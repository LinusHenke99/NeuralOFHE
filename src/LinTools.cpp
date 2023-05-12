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
    std::vector<bool> isZero;
    return parallel ?
           matrix_multiplication_parallel(matrix, vector, context):
           matrix_multiplication_sequential(matrix, vector, context);
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

    //  Calculating first term in the sum in order to avoid passing the private key to encrypt 0 and than later adding
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

    //  This will use the same procedure as above but it will include parallel computing
    auto diagonals = diagonal_transformation(
            resizeMatrix(matrix, batchSize, batchSize)
            );

    unsigned int n1 = find_n1(batchSize);
    unsigned int n2 = batchSize / n1;

    Plaintext pl = context->MakeCKKSPackedPlaintext(diagonals[0]);
    Ciphertext<DCRTPoly> subResult = context->EvalMult(pl, vector);

    auto cipherPrecompute = context->EvalFastRotationPrecompute(vector);
    uint32_t M = 2 * context->GetRingDimension();

    std::vector<Ciphertext<DCRTPoly>> rotCache;
    //  A vector which stores the job of each thread in the for of a future object. Each future object will return a two
    //  dimensional C++ array, which will have rotation that should be cached for the term submitted to the job, and the
    //  second element will be the term in the sum which should be added to subResult later
    std::vector<std::future<std::array<Ciphertext<DCRTPoly>, 2>>> futures1;

    for (unsigned int j=1; j<n1; j++) {
        //  Pushing the job to the futures1 vector
        futures1.push_back(std::async(
                std::launch::async,
                [&context, &diagonals, &cipherPrecompute, &vector, j, M] () -> std::array<Ciphertext<DCRTPoly>, 2> {
                    std::array<Ciphertext<DCRTPoly>, 2> result;
                    Plaintext pl = context->MakeCKKSPackedPlaintext(diagonals[j]);
                    Ciphertext<DCRTPoly> rotation = context->EvalFastRotation(vector, j, M, cipherPrecompute);
                    result[0] = rotation;
                    result[1] = context->EvalMult(pl, rotation);

                    return result;
                }
        ));
    }

    //  Looping over the elements of the futures vector in order to receive the results and cache the rotation and add
    //  the single terms to the sum to the result
    for (unsigned int j=0; j<n1-1; j++) {
        std::array<Ciphertext<DCRTPoly>, 2> buffer = futures1[j].get();

        rotCache.push_back(buffer[0]);
        subResult += buffer[1];
    }

    futures1.clear();

    Ciphertext<DCRTPoly> result = subResult;

    //  Generating a different vector of futures, because the return values of the threads are of different type
    std::vector<std::future<Ciphertext<DCRTPoly>>> futures2;

    for (unsigned int k=1; k<n2; k++) {
        pl = context->MakeCKKSPackedPlaintext(rotate_plain(diagonals[k*n1], -k*n1));
        subResult = context->EvalMult(pl, vector);

        futures2.push_back(std::async(
                std::launch::async,
            [&rotCache, &diagonals, &context, k, n1] (Ciphertext<DCRTPoly> subResult) -> Ciphertext<DCRTPoly> {
                std::vector<std::future<Ciphertext<DCRTPoly>>> tasks;

                for (unsigned int j = 1; j < n1; j++) {
                    if (!std::all_of(diagonals[k * n1 + j].begin(), diagonals[k * n1 + j].end(), [](double x) {return x == .0;})) {
                        Plaintext pl = context->MakeCKKSPackedPlaintext(rotate_plain(diagonals[k * n1 + j], -k * n1));
                        subResult += context->EvalMult(pl, rotCache[j - 1]);
                    }
                }

                return context->EvalRotate(subResult, k*n1);
            },
            subResult
        ));

    }

    for (unsigned int k=0; k<n2-1; k++) {
        result += futures2[k].get();
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


