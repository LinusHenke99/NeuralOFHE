#ifndef NEURALOFHE_OPERATOR_H
#define NEURALOFHE_OPERATOR_H

#include <string>
#include "LinTools.h"
#include "openfhe.h"

using namespace lbcrypto;

class Operator {
public:
    Operator();

    Operator(uint32_t& objectCounter, std::string name);

    virtual Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) = 0;

    static void initialize(CryptoContext<DCRTPoly> cc, uint32_t bs);

    void isInitialized();

    std::string getName();

protected:
    static uint32_t currentBatchsize;
    static uint32_t currentChannels;
    static CryptoContext<DCRTPoly> context;

    std::string name;
};


#endif //NEURALOFHE_OPERATOR_H
