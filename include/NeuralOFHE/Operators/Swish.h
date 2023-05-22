#ifndef NEURALOFHE_SWISH_H
#define NEURALOFHE_SWISH_H

#include "Activation.h"

namespace nn {
    class Swish : public ActivationFunction {
    public:

        Swish(double min, double max, unsigned int polyDeg=sharedPolyDeg,
              std::string name="Swish_" + std::to_string(numSwish));

        void setSharedDegree(uint32_t degree);

    private:
        static uint32_t numSwish;
        static uint32_t sharedPolyDeg;

        const static std::function<double (double)> swish;

        const std::function<double (double)> &getFunc() override;
    };
}

#endif //NEURALOFHE_SWISH_H
