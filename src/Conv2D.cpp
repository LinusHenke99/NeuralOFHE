#include "Conv2D.h"

uint32_t nn::Conv2D::numConv = 0;
std::string nn::Conv2D::baseName = "Conv2D_";


void nn::Conv2D::setParams(std::vector<std::vector<double>> mat, std::vector<double> bia) {
    this->matrix = mat;
    this->bias = bia;

    numConv++;
}


nn::Conv2D::Conv2D(std::vector<std::vector<double>> matrix, std::vector<double> bias) : Operator(numConv, baseName) {
    setParams(matrix, bias);
}


nn::Conv2D::Conv2D(std::vector<std::vector<double>> matrix, std::vector<double> bias, std::string name) : Operator(name) {
    setParams(matrix, bias);
}


Ciphertext<DCRTPoly> nn::Conv2D::forward(Ciphertext<DCRTPoly> x) {
    if (matrix[0].size() != currentBatchsize) {
        std::cout << "Invalid shape for " << name << ". Shape (" << matrix.size() << ", " << matrix[0].size() << ") " <<
        "could not be multiplied with batchsize " << currentBatchsize << std::endl;
        exit(1);
    }

    currentBatchsize = matrix.size();

    Plaintext biasPL = context->MakeCKKSPackedPlaintext(bias);

    x = matrix_multiplication(matrix, x, context);

    x = context->EvalAdd(x, biasPL);

    return x;
}
