#include "NeuralOFHE/Operators/Conv2D.h"
#include "LinTools.h"

uint32_t nn::Conv2D::numConv = 0;


nn::Conv2D::Conv2D(std::vector<std::vector<double>> weights, std::vector<double> bias) : Operator(numConv, "Conv2D_" +  std::to_string(numConv)) {
    setParams(weights, bias);
}


void nn::Conv2D::setParams(std::vector<std::vector<double>> mat, std::vector<double> bia) {
    this->weights = mat;
    this->bias = bia;
}


Ciphertext<DCRTPoly> nn::Conv2D::forward(Ciphertext<DCRTPoly> x) {
    Plaintext biasPL = context->MakeCKKSPackedPlaintext(bias);

    x = matrix_multiplication(weights, x, context);

    x = context->EvalAdd(x, biasPL);

    return x;
}
