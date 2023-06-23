#ifndef NEURALOFHE_ACTIVATION_H
#define NEURALOFHE_ACTIVATION_H

#include "Operator.h"


/***
 * Base class for activation functions.
 */
class ActivationFunction : public Operator{
public:
    /***
     * Constructor of an ActivationFunction object.
     *
     * @param Min
     * @param Max
     * @param polyDeg
     * @param objCounter
     * @param name
     */
    ActivationFunction(double Min, double Max, uint32_t polyDeg, uint32_t& objCounter, std::string name);

    /***
     * Applying the activation function to the input.
     *
     * @param x Input
     * @return Output
     */
    Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

protected:
    /***
     * Minimum, maximum and degree of the polynomial needed for the Chebyshev approximation.
     */
    double Min, Max;
    uint32_t polyDeg;

    /***
     * Virtual method implemented in order to return the corresponding activation function as C++ lambda. This is the
     * only member which needs implementation for inherited activation functions.
     *
     * @return Plain activation function
     */
    virtual const std::function<double (double)> &getFunc() = 0;
};

#endif //NEURALOFHE_ACTIVATION_H
