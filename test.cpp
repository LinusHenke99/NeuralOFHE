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
    params.SetScalingModSize(30);
    params.SetFirstModSize(35);

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

    auto conv = AddOperation<nn::Conv2D>(matrix, bias);

    std::vector<double> vec = {0.3, 1.};
    Plaintext pl = context->MakeCKKSPackedPlaintext(vec);
    auto cipher = context->Encrypt(pl, keys.publicKey);

    cipher = conv->forward(cipher);

    context->Decrypt(keys.secretKey, cipher, &pl);
    pl->SetLength(2);

    std::cout << pl;

    std::cout << "Name: " << conv->getName() << std::endl;

    return 0;
}