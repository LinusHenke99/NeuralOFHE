#include "NeuralOFHE/Operators/AveragePool.h"


uint32_t nn::AveragePool::numAvgPool = 0;


nn::AveragePool::AveragePool(matVec matrix) : 
    GeneralLinearOperator(matrix, numAvgPool, "AvgPool_" + std::to_string(numAvgPool)) {

}
