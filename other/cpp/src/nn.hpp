#ifndef NN_HPP
#define NN_HPP
#include <eigen3/Eigen/Dense>
#include <vector>

namespace eig = Eigen;

namespace nn {

class NeuralNetwork {
public:
  NeuralNetwork(std::vector<int> levels);
  NeuralNetwork(unsigned int n, int levels[]);
  eig::VectorXd evaluate(eig::VectorXd input);
  void setTeta(eig::MatrixXd teta, uint32_t id);
  // void setTeta(eig::VectorXd teta, uint32_t id);
  eig::VectorXd vecotrializeTetas();
  eig::MatrixXd teta(uint32_t id);
  void reset();

protected:
  std::vector<int> levels_;
  std::vector<eig::MatrixXd> tetas_;
};
};

#endif
