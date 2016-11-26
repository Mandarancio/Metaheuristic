#include "rsolution.hpp"
#include "exmath.hpp"
#include <iostream>
#include <sstream>
using namespace meta;

RnSolution::RnSolution(eig::VectorXd sol, eig::VectorXd mins,
                       eig::VectorXd maxs, double (*f)(eig::VectorXd))
    : min_(mins), max_(maxs), solution_(sol), fitness_function_(f) {
  // std::cout<<"SOL: "<<sol.toString()<<std::endl;
  // std::cout<<"NEW SOL: "<<solution_.toString()<<std::endl;
  n_ = sol.rows() * sol.cols();
}

RnSolution::RnSolution(uint32_t n, eig::VectorXd mins, eig::VectorXd maxs,
                       double (*f)(eig::VectorXd))
    : n_(n), min_(mins), max_(maxs), solution_(n_), fitness_function_(f) {
  for (uint32_t i = 0; i < n; i++) {
    solution_(i) = math::r() * (max_(i) - min_(i)) + min_(i);
  }
}

RnSolution::RnSolution(eig::VectorXd sol, double min, double max,
                       double (*f)(eig::VectorXd))
    : n_(sol.size()), min_(eig::VectorXd::Constant(sol.size(), min)),
      max_(eig::VectorXd::Constant(sol.size(), max)), solution_(sol),
      fitness_function_(f) {}

RnSolution::~RnSolution() {}

double RnSolution::max(int d) { return max_(d); }

double RnSolution::min(int d) { return min_(d); }

eig::VectorXd RnSolution::max() { return max_; }

eig::VectorXd RnSolution::min() { return min_; }

eig::VectorXd RnSolution::solution() { return solution_; }

ASolution *RnSolution::neighbour(int i, int j) {
  eig::VectorXd clone = solution_;
  clone(j) = solution_(j);
  clone(j) = solution_(i);
  return new RnSolution(clone, min_, max_, fitness_function_);
}

ASolution *RnSolution::random() {
  eig::VectorXd r(n_);
  // eig::VectorXd r(n_);
  for (uint32_t i = 0; i < n_; i++) {
    double x = double(rand()) / RAND_MAX * (max_(i) - min_(i)) + min_(i);
    r(i) = x;
  }
  eig::VectorXd m = min_;
  eig::VectorXd M = max_;
  RnSolution *x = new RnSolution(r, m, M, fitness_function_);
  return x;
}

ASolution *RnSolution::rand_neighbour() { return random(); }

ASolution *RnSolution::sub_solution(int i, int j) { return NULL; }

std::vector<ASolution *> RnSolution::neighbours() {
  std::vector<ASolution *> r;
  for (uint32_t i = 0; i < n_; i++) {
    r.push_back(random());
  }
  return r;
}

ASolution *RnSolution::create(std::vector<int> is) {
  eig::VectorXd x(n_);
  for (uint32_t i = 0; i < n_; i++) {
    x(i) = solution_(is[i]);
  }
  return new RnSolution(x, min_, max_, fitness_function_);
}

double RnSolution::sub_fitness(int i, int j) { return 0; }
double RnSolution::fitness() { return fitness_function_(solution_); }

int RnSolution::n() { return n_; }

RnSolution *RnSolution::create(eig::VectorXd x) {
  return new RnSolution(x, min_, max_, fitness_function_);
}

std::string RnSolution::to_string() {
  std::stringstream bff;
  bff << "[" << solution_(0);
  for (uint32_t i = 1; i < n_; i++) {
    bff << ", " << solution_(i);
  }
  bff << "] : " << fitness();
  return bff.str();
}
