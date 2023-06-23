#ifndef NEURALOFHE_CONV2D_H
#define NEURALOFHE_CONV2D_H

#include "Operator.h"
#include <vector>

namespace nn {
    class Conv2D : public Operator {
    public:
        /***
         * Convolutional layers can also be viewed as a matrix multiplication on a flattened input.
         *
         * @param weights Transformed matrix containing the Convolutional operation.
         * @param bias Transformed biases.
         */
        Conv2D(std::vector<std::vector<double>> weights, std::vector<double> bias);

        Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

    private:
        std::vector<std::vector<double>> weights;
        std::vector<double> bias;

        static uint32_t numConv;
    };
}

#endif //NEURALOFHE_CONV2D_H
