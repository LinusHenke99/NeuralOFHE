#ifndef NEURALOFHE_RELU_H
#define NEURALOFHE_RELU_H

#include "Activation.h"
#include <math.h>


namespace nn {
    class ReLU : public ActivationFunction {
    public:

        ReLU(double min, double max, unsigned int polyDeg=3);

    private:
        static uint32_t numReLU;

        const static std::function<double (double)> relu;

        const std::function<double (double)> &getFunc() override;
    };
}

#endif //NEURALOFHE_RELU_H
