#include "NeuralOFHE/Operators/Conv2D.h"
#include "LinTools.h"

uint32_t nn::Conv2D::numConv = 0;


nn::Conv2D::Conv2D(std::vector<std::vector<double>> weights, std::vector<double> bias) : Operator(numConv, "Conv2D_" +  std::to_string(numConv)) {
    this->weights = weights;
    this->bias = bias;
}


Ciphertext<DCRTPoly> nn::Conv2D::forward(Ciphertext<DCRTPoly> x) {
    Plaintext biasPL = context->MakeCKKSPackedPlaintext(bias);

    x = matrix_multiplication(weights, x, context);

    x = context->EvalAdd(x, biasPL);

    return x;
}
