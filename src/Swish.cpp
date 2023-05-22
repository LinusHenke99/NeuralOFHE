#include "../include/NeuralOFHE/Operators/Swish.h"

uint32_t nn::Swish::numSwish = 0;
uint32_t nn::Swish::sharedPolyDeg = 0;

const std::function<double (double)> nn::Swish::swish = [] (double x) -> double {return x / (1 + exp(-x));};
const std::function<double(double)> &nn::Swish::getFunc() {return swish;}


void nn::Swish::setSharedDegree(uint32_t degree) {
    sharedPolyDeg = degree;
}


nn::Swish::Swish(double min, double max, unsigned int polyDeg, std::string name)
: ActivationFunction(min, max, polyDeg, numSwish, name) {

}