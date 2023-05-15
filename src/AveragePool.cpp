#include "AveragePool.h"


nn::AveragePool::AveragePool(uint32_t kernelSize, uint32_t numChannels, std::string name) : Operator(numAvgPool, name) {
    this->kernelSize = kernelSize;
    this->numChannels = numChannels;
}


Ciphertext<DCRTPoly> nn::AveragePool::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    return matrix_multiplication(matrix, x, context);
}
