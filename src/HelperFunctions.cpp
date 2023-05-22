#include "NeuralOFHE/Helperfunctions/HelperFunctions.h"


void InitializeCryptoEnvironment(CryptoContext<DCRTPoly> context, uint32_t inputSize, uint32_t inputChannels) {
    Operator::initialize(context, inputSize, inputChannels);
}
