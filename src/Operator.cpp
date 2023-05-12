#include "Operator.h"

CryptoContext<DCRTPoly> Operator::context = NULL;
uint32_t Operator::currentBatchsize = 0;


Operator::Operator(uint32_t objectCounter, std::string baseName) {
    Operator::isInitialized();
    this->name = baseName + std::to_string(objectCounter);
}


Operator::Operator(std::string name) {
    Operator::isInitialized();
    this->name = name;
}


void Operator::initialize(CryptoContext<lbcrypto::DCRTPoly> cc, uint32_t bs) {
    context = cc;
    currentBatchsize = bs;
}


void Operator::isInitialized() {
    bool thrown = false;

    if (context == NULL && currentBatchsize == 0) {
        std::cout << "You first have to assign a Cryptocontext and an initial input size to the Operator class." << std::endl;
        thrown = true;
    }
    else if (context == NULL) {
        std::cout << "You first have to assign a Cryptocontext to the Operator class." << std::endl;
        thrown = true;
    }
    else if (currentBatchsize == 0) {
        std::cout << "You first have to assign an initial input size to the Operator class." << std::endl;
        thrown = true;
    }

    if (thrown) {
        std::cout << "Can be done by calling the InitializeCryptoEnvironment function" << std::endl;
        exit(1);
    }
}


std::string Operator::getName() {
    return this->name;
}