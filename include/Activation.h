#ifndef NEURALOFHE_ACTIVATION_H
#define NEURALOFHE_ACTIVATION_H

#include "Operator.h"

class ActivationFunction : public Operator{
public:
    ActivationFunction(double Min, double Max, uint32_t polyDeg, uint32_t& objCounter, std::string name);

    Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

protected:
    double Min, Max;
    uint32_t polyDeg;

    virtual const std::function<double (double)> &getFunc() = 0;
};

#endif //NEURALOFHE_ACTIVATION_H
