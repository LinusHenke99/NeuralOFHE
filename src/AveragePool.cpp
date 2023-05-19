#include "../include/AveragePool.h"


uint32_t nn::AveragePool::numAvgPool = 0;


nn::AveragePool::AveragePool(uint32_t kernelSize, uint32_t strides,
                             std::string name) : Operator(numAvgPool, name) {
    this->kernelSize = kernelSize;
    this->strides = strides;

    this->matrix = calcMatrix();
}


Ciphertext<DCRTPoly> nn::AveragePool::forward(Ciphertext<lbcrypto::DCRTPoly> x) {
    currentBatchsize = matrix.size();
    return matrix_multiplication(matrix, x, context);
}


matVec nn::AveragePool::calcMatrix() {
    double normalization = 1. / (kernelSize * kernelSize);
    uint32_t batchSizePerChannel = currentBatchsize / currentChannels;
    uint32_t arraySize = sqrt(batchSizePerChannel);

    uint32_t outPutSize = (arraySize - kernelSize) / strides + 1;
    outPutSize *= outPutSize;

    std::cout << "outputsize for " << name << ": " << outPutSize << std::endl;

    matVec mat(outPutSize * currentChannels);

    // TODO: Does not work with more than one channel
    for (uint32_t numRow=0; numRow<outPutSize; numRow++) {
        std::vector<double> row(currentBatchsize);

        uint32_t x = numRow * strides % (arraySize-1);
        uint32_t y = numRow * strides / (arraySize-1);

        uint32_t index = x + y * arraySize;

        for (uint32_t i=0; i<kernelSize; i++) {
            if (i>=currentBatchsize || i+arraySize>=currentBatchsize) {
                std::cerr << "Something went wrong in matrix creation for Averagepooling at " << name << "." << std::endl;
                exit(1);
            }
            row[index + i] = normalization;
            row[index + i + arraySize] = normalization;
        }


        for (uint32_t channel=0; channel<currentChannels; channel++) {
            std::vector<double> copy = row;
            if (channel != 0) {
                int rotate = channel * batchSizePerChannel;
                std::rotate(copy.begin(), copy.begin() - rotate, copy.end());
            }

            mat[numRow + outPutSize * channel] = copy;
        }
    }

    return mat;
}
