#include "nn.hpp"
#include "exmath.hpp"

using namespace nn;

NeuralNetwork::NeuralNetwork(std::vector<int> levels) : levels_(levels) {
  for (unsigned int i = 0; i < levels.size() - 1; i++) {
    uint32_t n = levels[i];
    uint32_t m = levels[i + 1];
    tetas_.push_back(math::r(n, m));
  }
}

math::Vector<double> NeuralNetwork::evaluate(math::Vector<double> input) {
  math::Matrix<double> x = math::sigmoid(input);
  for (uint32_t i = 0; i < tetas_.size(); i++) {
    x = math::sigmoid(x * tetas_[i]);
  }
  if (x.rows() == 1) {
    return math::Vector<double>(x.size(), x);
  } else {
    throw ERROR;
  }
}

void NeuralNetwork::setTeta(math::Matrix<double> teta, uint32_t id) {
  tetas_[id] = teta;
}

void NeuralNetwork::setTeta(math::Vector<double> teta, uint32_t id) {
  tetas_[id] =
      math::Matrix<double>(tetas_[id].rows(), tetas_[id].columns(), teta);
}
