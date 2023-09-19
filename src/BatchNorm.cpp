#include "NeuralOFHE/Operators/BatchNorm.h"

uint32_t nn::BatchNorm::numBatchNorm = 0;


nn::BatchNorm::BatchNorm(matVec weights, std::vector<double> bias) : GeneralLinearOperator(weights, bias, numBatchNorm, "BatchNorm_" + std::to_string(numBatchNorm)){

}
