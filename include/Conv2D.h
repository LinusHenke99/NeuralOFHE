#ifndef NEURALOFHE_CONV2D_H
#define NEURALOFHE_CONV2D_H

#include "Operator.h"
#include <vector>

namespace nn {
    class Conv2D : public Operator {
    public:
        Conv2D(std::vector<std::vector<double>> weights, std::vector<double> bias,
               std::string name="Conv2D_" + std::to_string(numConv));

        Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

    private:
        void setParams(std::vector<std::vector<double>> weights, std::vector<double> bias);

        std::vector<std::vector<double>> weights;
        std::vector<double> bias;

        static uint32_t numConv;
    };
}

#endif //NEURALOFHE_CONV2D_H
