#include "mynn.hpp"
#include "exmath.hpp"
using namespace nn;
using namespace meta;
#include <iostream>
MyNeuralNetwork::MyNeuralNetwork(std::string i_path, std::string l_path)
    : NeuralNetwork(std::vector<int>({401, 26,1})), loader(i_path, l_path) {

    }

double MyNeuralNetwork::evalue(math::Vector<double> conf) {
  this->setTeta(conf, 0);
  double f = 0;
  for (uint32_t i = 0; i < 200; i++) {
    math::Vector<double> img = loader.imgAsVector(i);
    img.push_back(math::r());
    img.resize(1, 401);
    f += math::pow2(loader.label(i) - this->evaluate(img)[0]);
  }
  return f / loader.n();
}


MyRnSolution::MyRnSolution(math::Vector<double> sol, double mins, double maxs,
                           nn::MyNeuralNetwork *nn)
    : RnSolution(sol, mins, maxs, NULL), nn_(nn) {}

double MyRnSolution::fitness() { return nn_->evalue(this->solution()); }

MyRnSolution *MyRnSolution::create(math::Vector<double> x) {
  return new MyRnSolution(x, min(0), max(0), nn_);
}

ASolution *MyRnSolution::clone() {
  return new MyRnSolution(this->solution(), min(0), max(0), nn_);
}

ASolution *MyRnSolution::random() {
  std::vector<double> r(n());
  // math::Vector<double> r(n_);
  double min = this->min(0);
  double dx = this->max(0) - min;
  for (int i = 0; i < n(); i++) {
    double x = double(rand()) / RAND_MAX * dx + min;
    r[i] = x;
  }
  // math::Vector<double> m = min_;
  // math::Vector<double> M = max_;
  MyRnSolution *x =
      new MyRnSolution(math::Vector<double>(n(), r), min, this->max(0), nn_);
  return x;
}
