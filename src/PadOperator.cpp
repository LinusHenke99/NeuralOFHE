#include "NeuralOFHE/Operators/PadOperator.h"

uint32_t nn::PadOperator::numPadOperator = 0;

nn::PadOperator::PadOperator(matVec matrix, std::vector<double> bias) : 
    GeneralLinearOperator(matrix, bias, numPadOperator, "PadOperator_" + std::to_string(numPadOperator)) {

}
