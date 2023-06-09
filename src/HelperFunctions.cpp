#include "NeuralOFHE/Helperfunctions/HelperFunctions.h"


void InitializeCryptoEnvironment(CryptoContext<DCRTPoly> context) {
    Operator::initialize(context);
}
