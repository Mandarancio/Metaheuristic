#ifndef NN_HPP
#define NN_HPP
#include "matrix.hpp"
#include <vector>

namespace nn {

class NeuralNetwork {
public:
  NeuralNetwork(std::vector<int> levels);
  NeuralNetwork(unsigned int n, int levels[]);
  math::Vector<double> evaluate(math::Vector<double> input);
  void setTeta(math::Matrix<double> teta, uint32_t id);
  void setTeta(math::Vector<double> teta, uint32_t id);
  math::Vector<double> vecotrializeTetas();

private:
  std::vector<int> levels_;
  std::vector<math::Matrix<double>> tetas_;
};
};

#endif
