#include "NeuralOFHE/Operators/BatchNorm.h"
#include "LinTools.h"

uint32_t nn::BatchNorm::numBatchNorm = 0;


nn::BatchNorm::BatchNorm(matVec weights, std::vector<double> bias) : Operator(numBatchNorm, "BatchNorm_" + std::to_string(numBatchNorm)){
    this->weights = weights;
    this->bias = bias;
}


Ciphertext<DCRTPoly> nn::BatchNorm::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    x = matrix_multiplication(weights, x, context);
    Plaintext pl = context->MakeCKKSPackedPlaintext(bias);
    x = context->EvalAdd(x, pl);

    return x;
}
