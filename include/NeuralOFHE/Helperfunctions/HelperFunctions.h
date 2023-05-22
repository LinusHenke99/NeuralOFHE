#ifndef NEURALOFHE_HELPERFUNCTIONS_H
#define NEURALOFHE_HELPERFUNCTIONS_H

#include <memory>
#include "../Operators/Operator.h"


void InitializeCryptoEnvironment(CryptoContext<DCRTPoly> context, uint32_t batchSize, uint32_t inputChannels);


// TODO: This did not work for instantianting ActivationFunction derivatives. Should be retested, since I did change the
// TODO: inheritance modifier.
template <typename Operation, typename... Args>
extern std::shared_ptr<Operator> AddOperation (Args... args) {
    std::shared_ptr<Operator> ptr(std::make_shared<Operation>(args...));

    return ptr;
}

#endif //NEURALOFHE_HELPERFUNCTIONS_H
