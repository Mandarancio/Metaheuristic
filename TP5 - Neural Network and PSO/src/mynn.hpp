#ifndef MYNN_HPP
#define MYNN_HPP
#include "img_loader.hpp"
#include "nn.hpp"
#include "rsolution.hpp"
#include <string>

namespace nn {

class MyNeuralNetwork : public NeuralNetwork {
public:
  MyNeuralNetwork(std::string i_path, std::string l_path);
  double evalue(eig::VectorXd conf);
  double precision(eig::VectorXd conf);
  eig::MatrixXd img_bias_;
  eig::MatrixXd l1_bias_;
  Loader loader;

private:
  eig::MatrixXd bias_;
};
};

namespace meta {

class MyRnSolution : public RnSolution {
public:
  MyRnSolution(eig::VectorXd sol, double mins, double maxs,
               nn::MyNeuralNetwork *nn);
  MyRnSolution(eig::VectorXd sol, eig::VectorXd mins, eig::VectorXd maxs,
               nn::MyNeuralNetwork *nn);
  virtual double fitness();
  virtual MyRnSolution *create(eig::VectorXd x);
  virtual ASolution *random();
  virtual ASolution *clone();

private:
  nn::MyNeuralNetwork *nn_;
};
};
#endif
