#include "NeuralOFHE/Operators/AveragePool.h"
#include "LinTools.h"


uint32_t nn::AveragePool::numAvgPool = 0;


nn::AveragePool::AveragePool(matVec matrix) : Operator(numAvgPool, "AvgPool_" + std::to_string(numAvgPool)) {
    this->matrix = matrix;
}


Ciphertext<DCRTPoly> nn::AveragePool::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    x = matrix_multiplication(matrix, x, context);

    return x;
}
