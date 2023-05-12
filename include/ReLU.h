#ifndef NEURALOFHE_RELU_H
#define NEURALOFHE_RELU_H

#include "Operator.h"
#include <math.h>


namespace nn {
    class ReLU : public Operator {
    public:

        ReLU(double min, double max, unsigned int polyDeg=sharedPolyDeg);

        ReLU(double min, double max, std::string name, unsigned int polyDeg=sharedPolyDeg);

        static void SetSharedDegree(uint32_t degree);

        Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

    private:
        double min, max;
        uint32_t polyDeg;

        void setParams(double mi, double ma, unsigned int deg);

        static uint32_t numReLU;
        static uint32_t sharedPolyDeg;

        static std::string baseName;
    };
}

#endif //NEURALOFHE_RELU_H
