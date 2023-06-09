#include "NeuralOFHE/Operators/BatchNorm.h"
#include "LinTools.h"

uint32_t nn::BatchNorm::numBatchNorm = 0;


void nn::BatchNorm::setParameters(std::vector<double> wei, std::vector<double> bia, double va, double m, double e) {
    this->weights = wei;
    this->bias = bia;
    this->var = va;
    this->mu = m;
    this->epsilon = e;
}


nn::BatchNorm::BatchNorm(std::vector<double> weights, std::vector<double> bias, double var,
                         double mu, double epsilon) : Operator(numBatchNorm, "BatchNorm_" + std::to_string(numBatchNorm)){
    setParameters(weights, bias, var, mu, epsilon);
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
