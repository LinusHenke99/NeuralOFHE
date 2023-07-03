#ifndef NEURALOFHE_BOOTSTRAPPING_H
#define NEURALOFHE_BOOTSTRAPPING_H

#include "Operator.h"

class BootStrapping : public Operator {
public:

    BootStrapping ();

    Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x) override;

private:
    static uint32_t numBootStrap;
};

#endif //NEURALOFHE_BOOTSTRAPPING_H
