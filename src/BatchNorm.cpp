#include "NeuralOFHE/Operators/BatchNorm.h"

uint32_t nn::BatchNorm::numBatchNorm = 0;


nn::BatchNorm::BatchNorm(std::vector<double> weights, std::vector<double> bias) : Operator(numBatchNorm, "BatchNorm_" + std::to_string(numBatchNorm)) {
    this->weights = weights;
    this->biases = bias;
}

Ciphertext<DCRTPoly> nn::BatchNorm::forward(Ciphertext<DCRTPoly> x) {
    Plaintext pl_weight = context->MakeCKKSPackedPlaintext(weights);
    Plaintext pl_biases = context->MakeCKKSPackedPlaintext(biases);

    Ciphertext<DCRTPoly> result = context->EvalMult(pl_weight, x);
    result = context->EvalAdd(pl_biases, result);

    return result;
}
