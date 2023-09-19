#ifndef NEURALOFHE_CONV2D_H
#define NEURALOFHE_CONV2D_H

#include "GeneralLinearOperator.h"
#include <vector>

namespace nn {
    class Conv2D : public GeneralLinearOperator {
    public:
        /***
         * Convolutional layers can also be viewed as a matrix multiplication on a flattened input.
         *
         * @param weights Transformed matrix containing the Convolutional operation.
         * @param bias Transformed biases.
         */
        Conv2D(std::vector<std::vector<double>> weights, std::vector<double> bias);

    private:
        static uint32_t numConv;
    };
}

#endif //NEURALOFHE_CONV2D_H
