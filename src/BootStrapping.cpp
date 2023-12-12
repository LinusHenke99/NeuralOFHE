#include "../include/NeuralOFHE/Operators/BootStrapping.h"


BootStrapping::BootStrapping() : Operator() {

}


Ciphertext<DCRTPoly> BootStrapping::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    Ciphertext<DCRTPoly> res = context->EvalBootstrap(x);

    return res;
}
