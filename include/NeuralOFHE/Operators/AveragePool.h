#ifndef NEURALOFHE_AVERAGEPOOL_H
#define NEURALOFHE_AVERAGEPOOL_H

#include <math.h>

#include "Operator.h"

namespace nn {
    class AveragePool : public Operator {
    public:
        /***
         * Average pooling can be transformed to be a matrix multiplication. Therefore an average pooling object only
         * stores a matrix as a private member
         *
         * @param matrix Matrix that contains the transformed average pooling operation.
         */
        AveragePool(matVec matrix);

        Ciphertext<DCRTPoly> forward (Ciphertext<DCRTPoly> x) override;

        matVec getMatrix() {return matrix;}

    private:
        matVec matrix;
        static uint32_t numAvgPool;
    };
}

#endif //NEURALOFHE_AVERAGEPOOL_H
