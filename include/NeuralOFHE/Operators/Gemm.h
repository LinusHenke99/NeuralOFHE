#ifndef NEURALOFHE_GEMM_H
#define NEURALOFHE_GEMM_H

#include "GeneralLinearOperator.h"

/***
 * General matrix multiplication class. Rest is self explanatory
 */
namespace nn {
    class Gemm : public GeneralLinearOperator {
    public:
        Gemm(matVec matrix, std::vector<double> bias);

    private:
        static uint32_t numGemm;

    };
}

#endif //NEURALOFHE_GEMM_H
