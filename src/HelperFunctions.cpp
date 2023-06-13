#include "NeuralOFHE/Helperfunctions/HelperFunctions.h"


void InitializeCryptoEnvironment(CryptoContext<DCRTPoly> context) {
    Operator::initialize(context);
}


std::vector<int> GetRotations (uint32_t batchSize) {
    std::set<int> resultSet;

    unsigned int n1 = (batchSize==0 || batchSize==1) ? 1 : 1 << (unsigned int) std::ceil(log2(batchSize));
    unsigned int n2 = batchSize / n1;

    for (unsigned int k=0; k<n2; k++) {
        resultSet.insert(k*n1);
        for (unsigned int j=0; j<n1; j++) {
            // resultSet.insert((k*n1 + j));
            resultSet.insert(j);
        }
    }

    std::vector<int> result(resultSet.size());
    std::copy(resultSet.begin(), resultSet.end(), result.begin());

    return result;
}
