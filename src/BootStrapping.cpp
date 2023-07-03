#include "../include/NeuralOFHE/Operators/BootStrapping.h"


BootStrapping::BootStrapping() : Operator(numBootStrap, "BootStrapping_" + std::to_string(numBootStrap)){

}


Ciphertext<DCRTPoly> BootStrapping::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    x = context->EvalBootstrap(x);

    return x;
}
