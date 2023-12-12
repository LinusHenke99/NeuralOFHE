#include "LinTools.h"


std::vector<double> rotate_plain(const std::vector<double>& vector, int index) {
    std::vector<double> result(vector.size());

    if(index == 0)
        return vector;
    else {
        if (index < 0)
            index = vector.size() + index % vector.size();

        for (unsigned int i = 0; i < vector.size(); i++) {
            unsigned int newIndex = (i + index) % vector.size();
            result[i] = vector[newIndex];
        }
    }

    return result;
}


Ciphertext<DCRTPoly> matrix_multiplication(
        const std::vector<std::vector<double>>& matrix,
        const Ciphertext<DCRTPoly>& vector,
        CryptoContext<DCRTPoly> context,
        bool parallel
) {
    Ciphertext<DCRTPoly> result = parallel ?
           matrix_multiplication_parallel(transpose(matrix), vector, context):
           matrix_multiplication_sequential(transpose(matrix), vector, context);

    //  The following Code is for tracking the size of a ciphertext
    uint32_t output_size = matrix[0].size();

    auto size = std::make_shared<MetadataTest>();
    size->SetMetadata(std::to_string(output_size));

    MetadataTest::StoreMetadata<DCRTPoly>(result, size);

    return result;
}


Ciphertext<DCRTPoly> matrix_multiplication_sequential (const std::vector<std::vector<double>>& matrix, const Ciphertext<DCRTPoly>& vector, CryptoContext<DCRTPoly> context) {
    uint32_t batchSize = vector->GetEncodingParameters()->GetBatchSize();

    //  Resizing matrix to the contexts batchSize and getting a matrix in diagonal order
    auto diagonals = diagonal_transformation(
            resizeMatrix(matrix, batchSize, batchSize)
            );


    //  Finding the optimal configuration for n1 and n2 where batchSize = n1 * n2
    unsigned int n1 = find_n1(batchSize);
    unsigned int n2 = batchSize / n1;

    //  Calculating first term in the sum in order to avoid passing the private key to encrypt 0 and then later adding
    //  to that via a for loop. Because of that for loops later will start at 1
    Plaintext pl = context->MakeCKKSPackedPlaintext(diagonals[0]);
    Ciphertext<DCRTPoly> subResult = context->EvalMult(pl, vector);

    //  Doing rotations precompute in order to optimize rotations of the ciphertext
    auto cipherPrecompute = context->EvalFastRotationPrecompute(vector);
    uint32_t M = 2 * context->GetRingDimension();

    //  Calculating first sub-sum and caching all rotations of the vector variable needed later
    std::vector<Ciphertext<DCRTPoly>> rotCache;
    for (unsigned int j=1; j<n1; j++) {
        Ciphertext<DCRTPoly> rotation = context->EvalFastRotation(vector, j, M, cipherPrecompute);
        rotCache.push_back(rotation);

        if (!std::all_of(diagonals[j].begin(), diagonals[j].end(), [](double x) {return x==.0;})) {
            pl = context->MakeCKKSPackedPlaintext(diagonals[j]);
            subResult += context->EvalMult(pl, rotation);
        }
    }

    Ciphertext<DCRTPoly> result = subResult;

    //  Calculating the remaining terms in the sums
    for (unsigned int k=1; k<n2; k++) {
        pl = context->MakeCKKSPackedPlaintext(rotate_plain(diagonals[k*n1], -k*n1));
        subResult = context->EvalMult(pl, vector);

        for (unsigned int j=1; j<n1; j++) {
            if (!std::all_of(diagonals[k*n1 + j].begin(), diagonals[k*n1 + j].end(), [](double x) {return x == .0;})) {
                pl = context->MakeCKKSPackedPlaintext(rotate_plain(diagonals[k * n1 + j], -k * n1));
                subResult += context->EvalMult(pl, rotCache[j - 1]);
            }
        }

        result += context->EvalRotate(subResult, k*n1);
    }

    return result;
}


Ciphertext<DCRTPoly> matrix_multiplication_parallel(const std::vector<std::vector<double>>& matrix, const Ciphertext<DCRTPoly>& vector, CryptoContext<DCRTPoly> context) {
    uint32_t batchSize = vector->GetEncodingParameters()->GetBatchSize();

    //  Resizing matrix to the contexts batchSize and getting a matrix in diagonal order
    auto diagonals = diagonal_transformation(
            resizeMatrix(matrix, batchSize, batchSize)
    );


    //  Finding the optimal configuration for n1 and n2 where batchSize = n1 * n2
    unsigned int n1 = find_n1(batchSize);
    unsigned int n2 = batchSize / n1;

    //  Calculating first term in the sum in order to avoid passing the private key to encrypt 0 and then later adding
    //  to that via a for loop. Because of that for loops later will start at 1
    Plaintext pl = context->MakeCKKSPackedPlaintext(diagonals[0]);
    Ciphertext<DCRTPoly> subResult = context->EvalMult(pl, vector);

    //  Doing rotations precompute in order to optimize rotations of the ciphertext
    auto cipherPrecompute = context->EvalFastRotationPrecompute(vector);
    uint32_t M = 2 * context->GetRingDimension();

    //  Calculating first sub-sum and caching all rotations of the vector variable needed later. In the sequential
    //  version the data is written by a push_back operation, this can not be done in parallel, since the order of the
    //  vector would then be false, depending on what thread finishes first
    std::vector<Ciphertext<DCRTPoly>> rotCache(n1 - 1);

    //  Adding parallelization in the form of an OpenMP for loop
    #pragma omp parallel for
    for (unsigned int j=1; j<n1; j++) {
        //  Adding to variables that are used by each thread in order to store separate sub results
        Plaintext subPlain;
        Ciphertext<DCRTPoly> subCipher;

        Ciphertext<DCRTPoly> rotation = context->EvalFastRotation(vector, j, M, cipherPrecompute);

        if (!std::all_of(diagonals[j].begin(), diagonals[j].end(), [](double x) {return x==.0;})) {
            subPlain = context->MakeCKKSPackedPlaintext(diagonals[j]);

            //  The subResult variable should only be written to by one thread at a time
            #pragma omp critical
            subResult += context->EvalMult(subPlain, rotation);
        }

        //  Same goes for the rotation cache
        #pragma omp critical
        rotCache[j-1] = rotation;
    }

    Ciphertext<DCRTPoly> result = subResult;

    //  Calculating the remaining terms in the sums
    #pragma omp parallel for
    for (unsigned int k = 1; k < n2; k++) {
        Ciphertext<DCRTPoly> subCipher;
        Plaintext subPlain;
        subPlain = context->MakeCKKSPackedPlaintext(rotate_plain(diagonals[k * n1], -k * n1));
        subCipher = context->EvalMult(subPlain, vector);

        for (unsigned int j = 1; j < n1; j++) {
            if (!std::all_of(diagonals[k * n1 + j].begin(), diagonals[k * n1 + j].end(),
                             [](double x) { return x == .0; })) {
                subPlain = context->MakeCKKSPackedPlaintext(rotate_plain(diagonals[k * n1 + j], -k * n1));
                subCipher += context->EvalMult(subPlain, rotCache[j - 1]);
            }
        }

        subCipher = context->EvalRotate(subCipher, k * n1);

        #pragma omp critical
        result += subCipher;
    }

    return result;
}


std::vector<double> plain_matrix_multiplication(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    std::vector<double> result;

    for (int i=0; i<(int) matrix.size(); i++) {
        double entry = 0;

        for (int j=0; j<(int) matrix[0].size(); j++) {
            entry += matrix[i][j] * vector[j];
        }

        result.push_back(entry);
    }

    return result;
}


std::vector<double> plain_addition(std::vector<double> a, const std::vector<double>& b) {
    for (int j=0; j<(int) a.size(); j++) {
        a[j] += b[j];
    }

    return a;
}


