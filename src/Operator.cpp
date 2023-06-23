#include "NeuralOFHE/Operators/Operator.h"

CryptoContext<DCRTPoly> Operator::context = NULL;


Operator::Operator(uint32_t& objectCounter, std::string name) {
    Operator::isInitialized();
    this->name = name;
    objectCounter++;
}


void Operator::initialize(CryptoContext<lbcrypto::DCRTPoly> cc) {
    context = cc;
}


void Operator::isInitialized() {
    if (context == NULL) {
        std::cerr << "You first have to initialize a cryptocontext using the 'SetContext' function." << std::endl;
        exit(1);
    }
}


std::string Operator::getName() {
    return this->name;
}