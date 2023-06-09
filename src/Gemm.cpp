#include "NeuralOFHE/Operators/Gemm.h"
#include "LinTools.h"

uint32_t nn::Gemm::numGemm = 0;


nn::Gemm::Gemm(matVec matrix, std::vector<double> bias) : Operator(numGemm, "Gemm_" + std::to_string(numGemm)) {
    this->matrix = matrix;
    this->bias = bias;
}


Ciphertext<DCRTPoly> nn::Gemm::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    x = matrix_multiplication(matrix, x, context);
    Plaintext pl = context->MakeCKKSPackedPlaintext(bias);

    x = context->EvalAdd(x, pl);

    return x;
}
