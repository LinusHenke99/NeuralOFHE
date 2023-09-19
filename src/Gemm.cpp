#include "NeuralOFHE/Operators/Gemm.h"

uint32_t nn::Gemm::numGemm = 0;


nn::Gemm::Gemm(matVec matrix, std::vector<double> bias) : GeneralLinearOperator(matrix, bias, numGemm, "Gemm_" + std::to_string(numGemm)) {

}
