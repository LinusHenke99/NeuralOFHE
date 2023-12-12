#ifndef NEURALPY_PADOPERATOR_H
#define NEURALPY_PADOPERATOR_H

#include "GeneralLinearOperator.h"

namespace nn {
    class PadOperator : public GeneralLinearOperator {
    public:
        PadOperator(matVec matrix, std::vector<double> bias);

    private:
        static uint32_t numPadOperator;

    };
}

#endif //NEURALPY_PADOPERATOR_H
