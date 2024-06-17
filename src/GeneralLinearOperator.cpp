#include "NeuralOFHE/Operators/GeneralLinearOperator.h"
#include "LinTools.h"


GeneralLinearOperator::GeneralLinearOperator(matVec weights, unsigned int& objCounter, std::string name) : Operator(objCounter, name) {
    this->weights = weights;
}

GeneralLinearOperator::GeneralLinearOperator(matVec weights, std::vector<double> biases, unsigned int& objCounter, std::string name) : Operator(objCounter, name) {
    this->weights = weights;
    this->biases = biases;
}

Ciphertext<DCRTPoly> GeneralLinearOperator::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    if (verbose)
        std::cout << "Carrying out matrix multiplication for " << name << std::endl;
    x = matrix_multiplication(weights, x, context);

    if (biases.size() != 0) {
        if (verbose)
            std::cout << "Adding biases for " << name << std::endl;
        Plaintext pl = context->MakeCKKSPackedPlaintext(biases);
        x = context->EvalAdd(x, pl);
    }

    return x;
}
