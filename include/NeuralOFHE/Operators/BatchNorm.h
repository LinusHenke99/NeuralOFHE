#ifndef NEURALOFHE_BATCHNORM_H
#define NEURALOFHE_BATCHNORM_H

#include "GeneralLinearOperator.h"

namespace nn {
    class BatchNorm : public GeneralLinearOperator {
    public:
        BatchNorm(std::vector<std::vector<double>> weights, std::vector<double> bias);

    private:
        /***
         * Operation counter.
         */
        static uint32_t numBatchNorm;
    };
}


#endif //NEURALOFHE_BATCHNORM_H
