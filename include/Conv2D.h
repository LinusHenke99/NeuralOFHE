//
// Created by lchenke on 12.05.23.
//

#ifndef NEURALOFHE_CONV2D_H
#define NEURALOFHE_CONV2D_H

#include "Operator.h"
#include <vector>

namespace nn {
    class Conv2D : public Operator {
    public:
        Conv2D(std::vector<std::vector<double>> matrix, std::vector<double> bias);

        Conv2D(std::vector<std::vector<double>> matrix, std::vector<double> bias, std::string name);

        Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

    private:
        void setParams(std::vector<std::vector<double>> matrix, std::vector<double> bias);

        std::vector<std::vector<double>> matrix;
        std::vector<double> bias;

        static uint32_t numConv;

        static std::string baseName;

    };
}

#endif //NEURALOFHE_CONV2D_H
