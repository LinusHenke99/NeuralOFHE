#ifndef NEURALOFHE_BATCHNORM_H
#define NEURALOFHE_BATCHNORM_H

#include "Operator.h"

namespace nn {
    class BatchNorm : public Operator {
    public:
        BatchNorm(std::vector<double> weights, std::vector<double> bias);

        Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

    private:
        /***
         * Operation counter.
         */
        static uint32_t numBatchNorm;

        std::vector<double> weights, biases;
    };
}


#endif //NEURALOFHE_BATCHNORM_H
