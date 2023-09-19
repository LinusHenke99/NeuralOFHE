#ifndef NEURALOFHE_AVERAGEPOOL_H
#define NEURALOFHE_AVERAGEPOOL_H

#include "GeneralLinearOperator.h"

namespace nn {
    class AveragePool : public GeneralLinearOperator {
    public:
        /***
         * Average pooling can be transformed to be a matrix multiplication. Therefore an average pooling object only
         * stores a matrix as a private member
         *
         * @param matrix Matrix that contains the transformed average pooling operation.
         */
        AveragePool(matVec matrix);

    private:
        static uint32_t numAvgPool;
    };
}

#endif //NEURALOFHE_AVERAGEPOOL_H
