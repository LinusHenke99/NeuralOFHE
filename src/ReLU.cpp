#include "NeuralOFHE/Operators/ReLU.h"

// Setting initial values for static variables
uint32_t nn::ReLU::numReLU = 0;

const std::function<double (double)> nn::ReLU::relu = [] (double x) -> double {return x <= 0 ? 0 : x;};
const std::function<double(double)> &nn::ReLU::getFunc() {return relu;}


nn::ReLU::ReLU(double min, double max, uint32_t polyDeg)
: ActivationFunction(min, max, polyDeg, numReLU, "ReLU_" + std::to_string(numReLU)) {
}
