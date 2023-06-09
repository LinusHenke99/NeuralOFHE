#include "../include/NeuralOFHE/Operators/Sigmoid.h"

uint32_t nn::Sigmoid::numSigmoid = 0;


const std::function<double (double)> nn::Sigmoid::sig = [] (double x) -> double {return 1/(1-exp(-x));};
const std::function<double(double)> &nn::Sigmoid::getFunc() {return sig;}


nn::Sigmoid::Sigmoid(double min, double max, uint32_t polyDeg)
: ActivationFunction(min, max, polyDeg, numSigmoid, "Sigmoid_" + std::to_string(numSigmoid)) {}
