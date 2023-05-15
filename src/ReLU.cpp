#include "ReLU.h"

// Setting initial values for static variables
uint32_t nn::ReLU::numReLU = 0;
uint32_t nn::ReLU::sharedPolyDeg = 0;

const std::function<double (double)> nn::ReLU::relu = [] (double x) -> double {return x <= 0 ? 0 : x;};
const std::function<double(double)> &nn::ReLU::getFunc() {return relu;}


void nn::ReLU::SetSharedDegree(uint32_t degree) {
    sharedPolyDeg = degree;
}


nn::ReLU::ReLU(double min, double max, uint32_t polyDeg, std::string name)
: ActivationFunction(min, max, polyDeg, numReLU, name) {
}
