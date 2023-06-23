#ifndef NEURALOFHE_SILU_H
#define NEURALOFHE_SILU_H

#include "Activation.h"

namespace nn {
    class SiLU : public ActivationFunction {
    public:

        SiLU(double min, double max, unsigned int polyDeg=3);

        void setSharedDegree(uint32_t degree);

    private:
        static uint32_t numSiLU;

        const static std::function<double (double)> silu;

        const std::function<double (double)> &getFunc() override;
    };
}

#endif //NEURALOFHE_SILU_H
