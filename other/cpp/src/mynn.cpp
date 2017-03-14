#include "mynn.hpp"
#include "exmath.hpp"
#include "pso.hpp"
using namespace nn;
using namespace meta;
#include <iostream>

MyNeuralNetwork::MyNeuralNetwork(std::string i_path, std::string l_path)
    : NeuralNetwork(std::vector<int>({401, 26, 1})), loader(i_path, l_path) {
  bias_ = eig::MatrixXd::Constant(200, 1, 1);
  eig::MatrixXd r_imgs = loader.imgs();
  img_bias_ = // loader.imgs();
      eig::MatrixXd(200, 401);
  img_bias_ << bias_, r_imgs;
  l1_bias_ = eig::MatrixXd::Constant(200, 1, 1);
}

double MyNeuralNetwork::evalue(eig::VectorXd conf) {
  eig::MatrixXd t0 = conf.segment(0, 401 * 25);
  t0.resize(401, 25);
  eig::MatrixXd t1 = conf.segment(401 * 25, 26);
  t1.resize(26, 1);
  eig::MatrixXd o0 = math::sigmoid(img_bias_ * t0);
  eig::MatrixXd o2(200, 26);
  o2 << l1_bias_, o0;
  eig::MatrixXd output = loader.labels() - math::sigmoid(o2 * t1);
  return output.squaredNorm() / loader.n();
}

double MyNeuralNetwork::precision(eig::VectorXd conf) {
  eig::MatrixXd t0 = conf.segment(0, 401 * 25);
  t0.conservativeResize(401, 25);
  this->tetas_[0] = t0;
  eig::MatrixXd t1 = conf.segment(401 * 25, 26);
  t1.conservativeResize(26, 1);
  this->tetas_[1] = t1;
  eig::MatrixXd o0 = math::sigmoid(img_bias_ * t0);
  eig::MatrixXd o2(200, 26);
  o2 << l1_bias_, o0;
  eig::MatrixXd output = math::sigmoid(o2 * t1);
  eig::MatrixXd labels = loader.labels();
  double p = 0;
  for (uint32_t i = 0; i < 200; i++) {
    int label = output(i) >= 0.5 ? 1 : 0;
    if (label == labels(i)) {
      p += 1;
    }
  }
  return p / 200;
}

MyRnSolution::MyRnSolution(eig::VectorXd sol, double mins, double maxs,
                           nn::MyNeuralNetwork *nn)
    : RnSolution(sol, mins, maxs, NULL), nn_(nn) {}

MyRnSolution::MyRnSolution(eig::VectorXd sol, eig::VectorXd mins,
                           eig::VectorXd maxs, nn::MyNeuralNetwork *nn)
    : RnSolution(sol, mins, maxs, NULL), nn_(nn) {}

double MyRnSolution::fitness() { return nn_->evalue(this->solution()); }

MyRnSolution *MyRnSolution::create(eig::VectorXd x) {
  return new MyRnSolution(x, this->min(), this->max(), nn_);
}

ASolution *MyRnSolution::clone() {
  eig::VectorXd clone(this->n());
  clone << this->solution();
  return new MyRnSolution(clone, min(), max(), nn_);
}

ASolution *MyRnSolution::random() {

  // eig::VectorXd r(n_);
  // double min = this->min(0);
  double max = this->max(0);
  eig::VectorXd r = eig::VectorXd::Random(n()) * max;
  MyRnSolution *x = new MyRnSolution(r, this->min(), this->max(), nn_);
  return x;
}
