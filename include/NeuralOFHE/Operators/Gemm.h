#ifndef NEURALOFHE_GEMM_H
#define NEURALOFHE_GEMM_H

#include "Operator.h"

namespace nn {
    class Gemm : public Operator {
    public:
        Gemm(matVec matrix, std::vector<double> bias);

        Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

    private:
        matVec matrix;
        std::vector<double> bias;

        static uint32_t numGemm;
    };
}

#endif //NEURALOFHE_GEMM_H
