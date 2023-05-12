#include "HelperFunctions.h"


void InitializeCryptoEnvironment(CryptoContext<DCRTPoly> context, uint32_t inputSize) {
    Operator::initialize(context, inputSize);
}
