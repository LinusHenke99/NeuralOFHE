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
    std::vector<int> rots = {1, 2};
    context->EvalRotateKeyGen(keys.secretKey, rots);

    InitializeCryptoEnvironment(context, 2);

    std::vector<double> vec = {0.3, 1.};

    nn::ReLU::SetSharedDegree(3);
    nn::BatchNorm::SetSharedEpsilon(0.0000001);

    nn::Conv2D conv(matrix, bias);
    nn::ReLU relu(-0.1, 0.1);
    nn::BatchNorm batchnorm(bias, bias, 0.01, 0.1);
    nn::ReLU relu2(-0.1, 0.1);

    Plaintext pl = context->MakeCKKSPackedPlaintext(vec);
    auto cipher = context->Encrypt(pl, keys.publicKey);

    std::cout << "Doing " << conv.getName() << std::endl;
    cipher = conv.forward(cipher);

    std::cout << "Doing " << relu.getName() << std::endl;
    cipher = relu.forward(cipher);

    std::cout << "Doing " << batchnorm.getName() << std::endl;
    cipher = batchnorm.forward(cipher);

    std::cout << "Doing " << relu2.getName() << std::endl;
    cipher = relu2.forward(cipher);

    context->Decrypt(keys.secretKey, cipher, &pl);
    pl->SetLength(2);

    std::cout << pl;

    return 0;
}