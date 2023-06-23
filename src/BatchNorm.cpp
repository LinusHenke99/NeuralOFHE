#include "NeuralOFHE/Operators/BatchNorm.h"
#include "LinTools.h"

uint32_t nn::BatchNorm::numBatchNorm = 0;


nn::BatchNorm::BatchNorm(std::vector<double> weights, std::vector<double> bias, double var,
                         double mu, double epsilon) : Operator(numBatchNorm, "BatchNorm_" + std::to_string(numBatchNorm)){
    this->weights = weights;
    this->bias = bias;
    this->var = var;
    this->mu = mu;
    this->epsilon = epsilon;
}


Ciphertext<DCRTPoly> nn::BatchNorm::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    auto initialTerm = context->EvalSub(x, mu);

    x = context->EvalMult(initialTerm, 1 / sqrt(var + epsilon));

    Plaintext pl = context->MakeCKKSPackedPlaintext(weights);
    x = context->EvalMult(x, pl);

    pl = context->MakeCKKSPackedPlaintext(bias);
    x = context->EvalAdd(x, pl);

    return x;
}
