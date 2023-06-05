#include "NeuralOFHE/Operators/Operator.h"

CryptoContext<DCRTPoly> Operator::context = NULL;
uint32_t Operator::currentBatchsize = 0;
uint32_t Operator::currentChannels = 0;


Operator::Operator(uint32_t& objectCounter, std::string name) {
    Operator::isInitialized();
    this->name = name;
    objectCounter++;
}


void Operator::initialize(CryptoContext<lbcrypto::DCRTPoly> cc, uint32_t bs, uint32_t channels) {
    context = cc;
    currentBatchsize = bs;
    currentChannels = channels;
}


void Operator::isInitialized() {
    if (context == NULL && currentBatchsize == 0 && currentChannels == 0) {
        std::cerr << "You first have to assign a Cryptocontext, an initial input size to the Operator class." << std::endl;
        std::cerr << "Can be done by calling the InitializeCryptoEnvironment function" << std::endl;
        exit(1);
    }
}


std::string Operator::getName() {
    return this->name;
}