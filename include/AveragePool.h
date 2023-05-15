#ifndef NEURALOFHE_AVERAGEPOOL_H
#define NEURALOFHE_AVERAGEPOOL_H

#include "Operator.h"

namespace nn {
    class AveragePool : public Operator {
    public:
        AveragePool (uint32_t kernelSize, uint32_t numChannels, std::string name="AvgPool_" + std::to_string(numAvgPool));

        Ciphertext<DCRTPoly> forward (Ciphertext<DCRTPoly> x) override;

    private:
        uint32_t kernelSize, numChannels;

        std::vector<std::vector<double>> matrix;
        static uint32_t numAvgPool;
    };
}

#endif //NEURALOFHE_AVERAGEPOOL_H
