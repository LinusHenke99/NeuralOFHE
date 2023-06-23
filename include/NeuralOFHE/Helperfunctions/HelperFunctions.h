#ifndef NEURALOFHE_HELPERFUNCTIONS_H
#define NEURALOFHE_HELPERFUNCTIONS_H

#include <memory>
#include "../Operators/Operator.h"


/***
 * Function that sets the context object for the entire crypto environment. Essentially just applies the static
 * Operator::initialize method, but gives a more intuitive naming
 *
 * @param context Context object that should be used
 */
void SetContext(CryptoContext<DCRTPoly> context);


/***
 * Function that generates a vector of ints which is filled with the indices needed for matrix multiplication according
 * to the contexts batchSize
 *
 * @param batchSize batchSize of the context
 * @return Vector of integers containing all needed rotation indices needed for matrix multiplication
 */
std::vector<int> GetRotations (uint32_t batchSize);


/***
 * Function that creates and returns shared pointer pointing to an Operator inherited object
 *
 * @tparam Operation Class of the Operation
 * @tparam Args
 * @param args Arguments of the classes constructor
 * @return Pointer to the Operation
 */
template <typename Operation, typename... Args>
extern std::shared_ptr<Operator> AddOperation (Args... args) {
    std::shared_ptr<Operator> ptr(std::make_shared<Operation>(args...));

    return ptr;
}

#endif //NEURALOFHE_HELPERFUNCTIONS_H
