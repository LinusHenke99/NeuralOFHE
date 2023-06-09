#ifndef NEURALOFHE_OPERATOR_H
#define NEURALOFHE_OPERATOR_H

#include <string>
#include <vector>
#include "openfhe.h"

using matVec = std::vector<std::vector<double>>;

using namespace lbcrypto;

class Operator {
public:
    Operator(uint32_t& objectCounter, std::string name);

    virtual Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) = 0;

    static void initialize(CryptoContext<DCRTPoly> cc);

    void isInitialized();

    std::string getName();

protected:
    static CryptoContext<DCRTPoly> context;

    std::string name;
};


#endif //NEURALOFHE_OPERATOR_H
