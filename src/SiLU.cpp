#include "../include/NeuralOFHE/Operators/SiLU.h"

uint32_t nn::SiLU::numSiLU = 0;

const std::function<double (double)> nn::SiLU::silu = [] (double x) -> double {return x / (1 + exp(-x));};
const std::function<double (double)> &nn::SiLU::getFunc() {return silu;}


nn::SiLU::SiLU(double min, double max, unsigned int polyDeg)
: ActivationFunction(min, max, polyDeg, numSiLU, "Swish_" + std::to_string(numSiLU)) {

}