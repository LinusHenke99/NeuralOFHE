#include "BatchNorm.h"

uint32_t nn::BatchNorm::numBatchNorm = 0;
double nn::BatchNorm::sharedEpsilon = .0;


void nn::BatchNorm::setParameters(std::vector<double> wei, std::vector<double> bia, double va, double m, double e) {
    this->weights = wei;
    this->bias = bia;
    this->var = va;
    this->mu = m;
    this->epsilon = e;

    if (epsilon=.0) {
        std::cerr << "Setting epsilon to 0 is not recommended. You can either set a value for epsilon for each instance"
                  << "of the  BatchNorm class, or set a shared epsilon using the nn::BatchNorm::SetSharedEpsilon"
                  << "method. Epsilon is zero for " << name << "." << std::endl;
    }
}


nn::BatchNorm::BatchNorm(std::vector<double> weights, std::vector<double> bias, double var,
                         double mu, std::string name, double epsilon) : Operator(numBatchNorm, name){
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


void nn::BatchNorm::SetSharedEpsilon(double eps) {
    sharedEpsilon = eps;
}
