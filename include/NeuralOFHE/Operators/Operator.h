#ifndef NEURALOFHE_OPERATOR_H
#define NEURALOFHE_OPERATOR_H

#include <string>
#include <vector>
#include "openfhe.h"

using matVec = std::vector<std::vector<double>>;

using namespace lbcrypto;

/***
 * Base class for all ML Operators.
 */
class Operator {
public:
    /***
     * Base constructor used to set the name of an object according to the object counter and increase that counter by
     * one.
     *
     * @param objectCounter Static variable of the inherited class which will be increased by the constructor
     * @param name Identifier of the object (Will use the counter for inherited classes)
     */
    Operator(uint32_t& objectCounter, std::string name);

    /***
     * Virtual function that represents applying the ML operation to the input x.
     *
     * @param x Input
     * @return Output
     */
    virtual Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) = 0;

    /***
     * Static method that sets the context object for all ML Operations, which then essentially initializes a
     * Crypto Environment.
     *
     * @param cc CryptoContext that should be used for the application
     */
    static void initialize(CryptoContext<DCRTPoly> cc);

    /***
     * Function that checks whether or not the context variable is pointing to NULL, i.e. not being initialized.
     */
    void isInitialized();

    /***
     * Getter method for the objects name.
     *
     * @return name
     */
    std::string getName();

protected:
    /***
     * Static variable pointing to the context object of the application.
     */
    static CryptoContext<DCRTPoly> context;

    /***
     * Name variable which can be useful for debugging applications.
     */
    std::string name;
};


#endif //NEURALOFHE_OPERATOR_H
