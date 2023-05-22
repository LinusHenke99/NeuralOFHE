#ifndef NEURALOFHE_BATCHNORM_H
#define NEURALOFHE_BATCHNORM_H

#include "Operator.h"

namespace nn {
    class BatchNorm : public Operator {
    public:
        BatchNorm(std::vector<double> weights, std::vector<double> bias, double var, double mu,
                  std::string name="BatchNorm_" + std::to_string(numBatchNorm), double epsilon=sharedEpsilon);

        Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

        static void SetSharedEpsilon(double eps);

    private:
        std::vector<double> weights, bias;
        double var, mu, epsilon;

        static uint32_t numBatchNorm;
        static double sharedEpsilon;

        void setParameters(std::vector<double> wei, std::vector<double> bia, double va, double m, double e);
    };
}


#endif //NEURALOFHE_BATCHNORM_H
