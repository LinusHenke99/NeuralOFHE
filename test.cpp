#include <iostream>
#include "InherOperators.h"
#include "HelperFunctions.h"


int main() {
    typedef std::vector<std::vector<double>> Matrix;

    Matrix matrix = {
            {1, 2},
            {3, 4}
    };

    std::vector<double> bias = {1, 2};

    CCParams<CryptoContextCKKSRNS> params;
    params.SetBatchSize(2);
    params.SetScalingTechnique(FLEXIBLEAUTO);
    params.SetSecurityLevel(lbcrypto::HEStd_128_classic);
    params.SetScalingModSize(50);
    params.SetFirstModSize(60);
    params.SetMultiplicativeDepth(15);

    CryptoContext<DCRTPoly> context = GenCryptoContext(params);
    context->Enable(PKE);
    context->Enable(LEVELEDSHE);
    context->Enable(KEYSWITCH);
    context->Enable(ADVANCEDSHE);

    auto keys = context->KeyGen();
    context->EvalMultKeyGen(keys.secretKey);
    std::vector<int> rots = {1, 2, 3};
    context->EvalRotateKeyGen(keys.secretKey, rots);

    InitializeCryptoEnvironment(context, 9, 1);

    nn::AveragePool avg(2, 1);

    matVec pool = avg.getMatrix();

    for (const auto& row : pool) {
        std::cout << "[\t";
        for (auto value : row) {
            if (value != .0) {
                std::cout << 1;
            } else {
                std::cout << 0;
            }
            std::cout << "\t";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}