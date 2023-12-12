#include "NeuralOFHE/Operators/Operator.h"

bool Operator::verbose = false;
bool Operator::testMode = false;


CryptoContext<DCRTPoly> Operator::context = NULL;


Operator::Operator() {}


Operator::Operator(uint32_t& objectCounter, std::string name) {
    Operator::isInitialized();
    this->name = name;
    objectCounter++;
}


void Operator::initialize(CryptoContext<lbcrypto::DCRTPoly> cc) {
    context = cc;
}


void Operator::isInitialized() {
    if (context == NULL && !testMode) {
        std::cerr << "You first have to initialize a cryptocontext using the 'SetContext' function." << std::endl;
        exit(1);
    }
}


std::string Operator::getName() {
    return this->name;
}


void Operator::setVerbosity(bool state) {
    verbose = state;
}


void Operator::setTest() {
    testMode = true;
}


bool Operator::getVerbosity() {
    return verbose;
}
