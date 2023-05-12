#include "ReLU.h"

uint32_t nn::ReLU::numReLU = 0;
uint32_t nn::ReLU::sharedPolyDeg = 0;
std::string nn::ReLU::baseName = "ReLU_";

void nn::ReLU::setParams(double mi, double ma, uint32_t deg) {
    this->min = mi;
    this->max = ma;
    this->polyDeg = deg;

    numReLU++;
}


void nn::ReLU::SetSharedDegree(uint32_t degree) {
    sharedPolyDeg = degree;
}


nn::ReLU::ReLU(double min, double max, unsigned int polyDeg) : Operator(numReLU, baseName){
    setParams(min, max, polyDeg);
}


nn::ReLU::ReLU(double min, double max, std::string name, unsigned int polyDeg) : Operator(name) {
    setParams(min, max, polyDeg);
}


Ciphertext<DCRTPoly> nn::ReLU::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    if (polyDeg == 0) {
        std::cout << "You either have to set an individual polynomial degree for each instance of the ReLU class, or" <<
        " call the nn::ReLU::SetSharedDegree function to set a positive nonzero default value. (Failed at instance: " <<
        name  << ")" << std::endl;
        exit(1);
    }

    auto relu = [] (double x) -> double {return x <= 0 ? 0 : 0;};
    x = context->EvalChebyshevFunction(relu, x, min, max, polyDeg);

    return x;
}
