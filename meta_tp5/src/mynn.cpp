#include "mynn.hpp"
#include "exmath.hpp"
#include "pso.hpp"
using namespace nn;
using namespace meta;

MyNeuralNetwork::MyNeuralNetwork(std::string i_path, std::string l_path)
    : NeuralNetwork(std::vector<int>({400, 25, 1})), loader(i_path, l_path) {}

double MyNeuralNetwork::evalue(eig::VectorXd conf) {
  eig::MatrixXd t0 = conf.segment(0, 400 * 25);
  eig::MatrixXd t1 = conf.segment(400 * 25, 25);
  this->setTeta(t0, 0);
  this->setTeta(t1, 1);
  double f = 0;
  for (uint32_t i = 0; i < loader.n(); i++) {
    eig::VectorXd img = loader.imgAsVector(i);
    f += math::pow2(loader.label(i) - this->evaluate(img)(0));
  }
  return f / loader.n();
}

MyRnSolution::MyRnSolution(eig::VectorXd sol, double mins, double maxs,
                           nn::MyNeuralNetwork *nn)
    : RnSolution(sol, mins, maxs, NULL), nn_(nn) {}

double MyRnSolution::fitness() { return nn_->evalue(this->solution()); }

MyRnSolution *MyRnSolution::create(eig::VectorXd x) {
  return new MyRnSolution(x, min(0), max(0), nn_);
}

ASolution *MyRnSolution::clone() {
  return new MyRnSolution(this->solution(), min(0), max(0), nn_);
}

ASolution *MyRnSolution::random() {

  // eig::VectorXd r(n_);
  double min = this->min(0);
  double dx = this->max(0) - min;
  eig::VectorXd r =
      eig::VectorXd::Constant(n(), min) + eig::VectorXd::Random(n()) * dx;
  MyRnSolution *x = new MyRnSolution(r, min, this->max(0), nn_);
  return x;
}
