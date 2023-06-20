#include "NeuralOFHE/Helperfunctions/HelperFunctions.h"


void SetContext(CryptoContext<DCRTPoly> context) {
    Operator::initialize(context);
}


std::vector<int> GetRotations (uint32_t batchSize) {
    std::set<int> resultSet;

    unsigned int n1;

    if ((int) log2(batchSize) % 2 == 0)
        n1 = sqrt(batchSize);
    else
        n1 = sqrt(1 << ((int) log2(batchSize) - 1));

    if (n1 < batchSize / n1)
        n1 = batchSize / n1;

    unsigned int n2 = batchSize / n1;

    for (unsigned int k=0; k<n2; k++) {
        resultSet.insert(k*n1);
        for (unsigned int j=0; j<n1; j++) {
            resultSet.insert(j);
        }
    }

    std::vector<int> result(resultSet.size());
    std::copy(resultSet.begin(), resultSet.end(), result.begin());

    return result;
}
