#include "nn.hpp"
#include "exmath.hpp"
using namespace nn;

NeuralNetwork::NeuralNetwork(std::vector<int> levels) : levels_(levels) {
  for (unsigned int i = 0; i < levels.size() - 1; i++) {
    uint32_t n = levels[i];
    uint32_t m = levels[i + 1];
    tetas_.push_back(math::r(n, m, 4.0, -2.0));
  }
}
NeuralNetwork::NeuralNetwork(unsigned int n, int levels[]) {
  for (unsigned int i = 0; i < n; i++) {
    levels_.push_back(levels[i]);
    if (i < n - 1) {
      uint32_t n = levels[i];
      uint32_t m = levels[i + 1];
      tetas_.push_back(math::r(n, m, 4.0, -2.0));
    }
  }
}

eig::VectorXd NeuralNetwork::evaluate(eig::VectorXd input) {
  eig::MatrixXd x = math::sigmoid(input).transpose();
  for (uint32_t i = 0; i < tetas_.size(); i++) {

    eig::MatrixXd prod = x * tetas_[i];
    x = math::sigmoid(prod);
  }
  if (x.rows() == 1) {
    return x;
  } else {
    throw - 20;
  }
}

void NeuralNetwork::setTeta(eig::MatrixXd teta, uint32_t id) {
  teta.resize(tetas_[id].rows(), tetas_[id].cols());
  tetas_[id] = teta;
}

// void NeuralNetwork::setTeta(eig::VectorXd teta, uint32_t id) {
// eig::MatrixXd x = teta;
// x.resize(tetas_[id].rows(), tetas_[id].cols());
// tetas_[id] = x; // eig::MatrixXd(tetas_[id].rows(), tetas_[id].cols(), teta);
// }

eig::VectorXd NeuralNetwork::vecotrializeTetas() {
  // eig::VectorXd a();
  uint32_t s = 0;
  for (uint32_t i = 0; i < tetas_.size(); i++) {
    s += tetas_[i].size();
  }

  eig::VectorXd a(s);
  uint32_t c = 0;
  for (uint32_t i = 0; i < tetas_.size(); i++) {
    for (uint32_t j = 0; j < tetas_[i].rows(); j++) {
      for (uint32_t k = 0; k < tetas_[i].cols(); k++) {
        a(c) = tetas_[i](j, k);
        c++;
      }
    }
  }
  return a;
}

void NeuralNetwork::reset() {
  for (unsigned int i = 0; i < levels_.size() - 1; i++) {
    uint32_t n = levels_[i];
    uint32_t m = levels_[i + 1];
    tetas_.push_back(math::r(n, m, 4.0, -2.));
  }
}

eig::MatrixXd NeuralNetwork::teta(uint32_t id) { return tetas_.at(id); }
