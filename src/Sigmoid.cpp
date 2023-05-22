#include "../include/NeuralOFHE/Operators/Sigmoid.h"

uint32_t nn::Sigmoid::numSigmoid = 0;
uint32_t nn::Sigmoid::sharedPolyDeg = 0;


const std::function<double (double)> nn::Sigmoid::sig = [] (double x) -> double {return 1/(1-exp(-x));};
const std::function<double(double)> &nn::Sigmoid::getFunc() {return sig;}


void nn::Sigmoid::setSharedPolyDeg(uint32_t degree) {
    sharedPolyDeg = degree;
}


nn::Sigmoid::Sigmoid(double min, double max, uint32_t polyDeg, std::string name)
: ActivationFunction(min, max, polyDeg, numSigmoid, name) {}
