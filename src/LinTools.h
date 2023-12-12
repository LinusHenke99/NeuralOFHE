/**
 * @file LinTools.h
 *
 * @brief Includes functions that are necessary for carrying out linear operations on plaintexts in the form C++ vectors
 * and ciphertexts in the for of CKKS OpenFHE Ciphertext objects. Function bodies are defined in src/LinTools.cpp.
 *
 * @author Linus Henke
 * Contact: linus.henke@mci.edu
 *
 */

#ifndef TEST_MNIST_LINTOOLS_H
#define TEST_MNIST_LINTOOLS_H

#include <vector>
#include <future>

#include "MatrixFormatting.h"
#include "UnitTestMetadataTestSer.h"
#include "openfhe.h"

using namespace lbcrypto;


/***
 * Function that does plaintext matrix with ciphertext vector multiplication with the option to turn off parallel
 * computing. Default is with parallel computing
 *
 * @param matrix Plaintext matrix, which should be multiplied with the vector
 * @param vector Ciphertext vector which should be multiplied
 * @param context Cryptocontext belonging to the ciphertext
 * @param parallel Boolean that toggles parallel computing
 */
Ciphertext<DCRTPoly> matrix_multiplication(
        const std::vector<std::vector<double>>& matrix,
        const Ciphertext<DCRTPoly>& vector,
        CryptoContext<DCRTPoly> context,
        bool parallel = true
        );


/***
 * Function that carries out a matrix multiplication between a plain matrix and an encrypted CKKS vector using the
 * baby-step giant-step diagonal method. The matrix will be resized to be a quadratic matrix according to the contexts
 * batch size.
 *
 * @param matrix Plaintext matrix, which should be multiplied with the vector
 * @param vector Ciphertext vector which should be multiplied
 * @param context Cryptocontext belonging to the ciphertext
 */
Ciphertext<DCRTPoly> matrix_multiplication_sequential(
        const std::vector<std::vector<double>>& matrix,
        const Ciphertext<DCRTPoly>& vector,
        CryptoContext<DCRTPoly> context
        );


/***
 * Function that works with the same principle as matrix_multiplication_diagonals but implements parallel computing
 *
 *
 * @param matrix Plaintext matrix, which should be multiplied with the vector
 * @param vector Ciphertext vector which should be multiplied
 * @param context Cryptocontext belonging to the ciphertext
 */
Ciphertext<DCRTPoly> matrix_multiplication_parallel(
        const std::vector<std::vector<double>>& matrix,
        const Ciphertext<DCRTPoly>& vector,
        CryptoContext<DCRTPoly> context
        );


/***
 * Function that carries out a plaintext vector-matrix multiplication. Mostly used for accuracy studies of the
 * ciphertext operations.
 *
 * @param matrix Plaintext matrix which should be multiplied with the plain vector
 * @param vector Plaintext vector which should be multiplied with the plain matrix
 */
std::vector<double> plain_matrix_multiplication(
        const std::vector<std::vector<double>>& matrix,
        const std::vector<double>& vector
        );


/***
 * Function that carries out addition between to plain vectors. Mostly used for accuracy studies of the ciphertext
 * operations
 *
 * @param a First vector of addition. Not passed as reference, because function needs an editable copy of one of summands
 * @param b Second vector of addition.
 */
std::vector<double> plain_addition(std::vector<double> a, const std::vector<double>& b);



Ciphertext<DCRTPoly> my_poly_eval (std::vector<double> coefs, Ciphertext<DCRTPoly> cipher);

#endif //TEST_MNIST_LINTOOLS_H
