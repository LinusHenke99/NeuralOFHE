#ifndef NEURALOFHE_AVERAGEPOOL_H
#define NEURALOFHE_AVERAGEPOOL_H

#include <math.h>

#include "Operator.h"

namespace nn {
    class AveragePool : public Operator {
    public:
        AveragePool (uint32_t kernelSize, uint32_t strides,
                     std::string name="AvgPool_" + std::to_string(numAvgPool));

        Ciphertext<DCRTPoly> forward (Ciphertext<DCRTPoly> x) override;

        matVec getMatrix() {return matrix;}

    private:
        uint32_t kernelSize, strides;

        matVec matrix;
        static uint32_t numAvgPool;

        matVec calcMatrix();
    };
}

#endif //NEURALOFHE_AVERAGEPOOL_H
