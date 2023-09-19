//
// Created by lchenke on 19.09.23.
//

#ifndef NEURALOFHE_GENERALLINEAROPERATOR_H
#define NEURALOFHE_GENERALLINEAROPERATOR_H

#include "Operator.h"

class GeneralLinearOperator : public Operator {
public:
    GeneralLinearOperator (matVec weights, unsigned int& objCounter, std::string name);

    GeneralLinearOperator (matVec weights, std::vector<double> biases, unsigned int& objCounter, std::string name);

    Ciphertext<DCRTPoly> forward (Ciphertext<DCRTPoly> x) override;

private:
    matVec weights;
    std::vector<double> biases;

};


#endif //NEURALOFHE_GENERALLINEAROPERATOR_H
