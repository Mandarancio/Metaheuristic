#include "nn.hpp"
#include "exmath.hpp"
#include <iostream>
using namespace nn;

NeuralNetwork::NeuralNetwork(std::vector<int> levels) : levels_(levels) {
  for (unsigned int i = 0; i < levels.size() - 1; i++) {
    uint32_t n = levels[i];
    uint32_t m = levels[i + 1];
    tetas_.push_back(math::r(n, m));
  }
}
NeuralNetwork::NeuralNetwork(unsigned int n, int levels[]) {
  for (unsigned int i = 0; i < n; i++) {
    levels_.push_back(levels[i]);
    if (i < n - 1) {
      uint32_t n = levels[i];
      uint32_t m = levels[i + 1];
      tetas_.push_back(math::r(n, m));
    }
  }
}

math::Vector<double> NeuralNetwork::evaluate(math::Vector<double> input) {
  math::Matrix<double> x = math::sigmoid(input);
  // std::cout << x.toMatFile("layer" + std::to_string(0)) << std::endl
  // << std::endl;
  for (uint32_t i = 0; i < tetas_.size(); i++) {
    math::Matrix<double> teta = tetas_[i];
    x = math::sigmoid(x * teta);
    // std::cout << teta.toMatFile("teta" + std::to_string(i)) << std::endl;
    // std::cout << x.toMatFile("layer" + std::to_string(i + 1)) << std::endl
    // << std::endl;
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

math::Vector<double> NeuralNetwork::vecotrializeTetas() {
  std::vector<double> v;
  for (uint32_t i = 0; i < tetas_.size(); i++) {
    // reserve() is optional - just to improve performance
    v.reserve(v.size() + distance(tetas_[i].begin(), tetas_[i].end()));
    v.insert(v.end(), tetas_[i].begin(), tetas_[i].end());
  }
  return math::Vector<double>(v.size(), v);
}
