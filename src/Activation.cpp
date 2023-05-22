#include "NeuralOFHE/Operators/Activation.h"


ActivationFunction::ActivationFunction(double Min, double Max, uint32_t polyDeg, uint32_t& objCounter,
                                       std::string name) : Operator(objCounter, name){
    this->Min = Min;
    this->Max = Max;
    this->polyDeg = polyDeg;
}


Ciphertext<DCRTPoly> ActivationFunction::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    std::function<double (double)> function = getFunc();
    return context->EvalChebyshevFunction(function, x, Min, Max, polyDeg);
}
