#include "Conv2D.h"

uint32_t nn::Conv2D::numConv = 0;
std::string nn::Conv2D::baseName = "Conv2D_";


void nn::Conv2D::setParams(std::vector<std::vector<double>> mat, std::vector<double> bia) {
    this->weights = mat;
    this->bias = bia;

    numConv++;
}


nn::Conv2D::Conv2D(std::vector<std::vector<double>> weights, std::vector<double> bias) : Operator(numConv, baseName) {
    setParams(weights, bias);
}


nn::Conv2D::Conv2D(std::vector<std::vector<double>> weights, std::vector<double> bias, std::string name) : Operator(name) {
    setParams(weights, bias);
}


Ciphertext<DCRTPoly> nn::Conv2D::forward(Ciphertext<DCRTPoly> x) {
    if (weights[0].size() != currentBatchsize) {
        std::cout << "Invalid shape for " << name << ". Shape (" << weights.size() << ", " << weights[0].size() << ") " <<
        "could not be multiplied with batchsize " << currentBatchsize << std::endl;
        exit(1);
    }

    currentBatchsize = weights.size();

    Plaintext biasPL = context->MakeCKKSPackedPlaintext(bias);

    x = matrix_multiplication(weights, x, context);

    x = context->EvalAdd(x, biasPL);

    return x;
}
