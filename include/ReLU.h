#ifndef NEURALOFHE_RELU_H
#define NEURALOFHE_RELU_H

#include "Activation.h"
#include <math.h>


namespace nn {
    class ReLU : public ActivationFunction {
    public:

        ReLU(double min, double max, unsigned int polyDeg=sharedPolyDeg,
             std::string name="ReLU_" + std::to_string(numReLU));

        static void SetSharedDegree(uint32_t degree);

    private:
        static uint32_t numReLU;
        static uint32_t sharedPolyDeg;

        const static std::function<double (double)> relu;

        const std::function<double (double)> &getFunc() override;
    };
}

#endif //NEURALOFHE_RELU_H
