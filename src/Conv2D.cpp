#include "NeuralOFHE/Operators/Conv2D.h"

uint32_t nn::Conv2D::numConv = 0;


nn::Conv2D::Conv2D(std::vector<std::vector<double>> weights, std::vector<double> bias) : GeneralLinearOperator(weights, bias, numConv, "Conv2D_" +  std::to_string(numConv)) {

}
