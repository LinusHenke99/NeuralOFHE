#include "../include/NeuralOFHE/Operators/Swish.h"

uint32_t nn::Swish::numSwish = 0;

const std::function<double (double)> nn::Swish::swish = [] (double x) -> double {return x / (1 + exp(-x));};
const std::function<double(double)> &nn::Swish::getFunc() {return swish;}


nn::Swish::Swish(double min, double max, unsigned int polyDeg)
: ActivationFunction(min, max, polyDeg, numSwish, "Swish_" + std::to_string(numSwish)) {

}