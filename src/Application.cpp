#include "NeuralOFHE/Application.h"


Application::Application(const std::vector<std::shared_ptr<Operator>> &layers) {
    this->layers = layers;
}


Ciphertext<DCRTPoly> Application::forward(Ciphertext<DCRTPoly> x) {
    for (const auto& layer : layers)
        x = layer->forward(x);

    return x;
}
