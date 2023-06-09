#ifndef NEURALOFHE_AVERAGEPOOL_H
#define NEURALOFHE_AVERAGEPOOL_H

#include <math.h>

#include "Operator.h"

namespace nn {
    class AveragePool : public Operator {
    public:
        AveragePool(matVec matrix);

        Ciphertext<DCRTPoly> forward (Ciphertext<DCRTPoly> x) override;

        matVec getMatrix() {return matrix;}

    private:
        matVec matrix;
        static uint32_t numAvgPool;

        matVec calcMatrix();
    };
}

#endif //NEURALOFHE_AVERAGEPOOL_H
