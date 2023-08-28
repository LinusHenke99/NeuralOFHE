#ifndef NEURALOFHE_BATCHNORM_H
#define NEURALOFHE_BATCHNORM_H

#include "Operator.h"

namespace nn {
    class BatchNorm : public Operator {
    public:
        BatchNorm(std::vector<std::vector<double>> weights, std::vector<double> bias);

        Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

    private:
        /***
         * Plaintext arguments given to the Batch-Normalization operation
         */
        std::vector<double> bias;
        matVec weights;

        /***
         * Operation counter.
         */
        static uint32_t numBatchNorm;
    };
}


#endif //NEURALOFHE_BATCHNORM_H
