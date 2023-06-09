#ifndef NEURALOFHE_SIGMOID_H
#define NEURALOFHE_SIGMOID_H

#include "Activation.h"

namespace nn {
    class Sigmoid : public ActivationFunction {
    public:
        Sigmoid(double min, double max, uint32_t polyDeg=3);

        static void setSharedPolyDeg (uint32_t degree);

    private:
        static uint32_t numSigmoid;

        static const std::function<double (double)> sig;

        const std::function<double (double)> &getFunc() override;

    };
}

#endif //NEURALOFHE_SIGMOID_H
