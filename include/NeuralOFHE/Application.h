#ifndef NEURALOFHE_APPLICATION_H
#define NEURALOFHE_APPLICATION_H

#include <vector>
#include <memory>

#include "Operators/InherOperators.h"


class Application {
public:
    Application(const std::vector<std::shared_ptr<Operator>>& layers);

    Ciphertext<DCRTPoly> forward(Ciphertext<DCRTPoly> x);

private:
    std::vector<std::shared_ptr<Operator>> layers;

};


#endif //NEURALOFHE_APPLICATION_H
