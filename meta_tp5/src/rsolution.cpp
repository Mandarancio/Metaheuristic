#include "rsolution.hpp"
#include "exmath.hpp"
#include <iostream>
#include <sstream>
using namespace meta;

RnSolution::RnSolution(math::Vector<double> sol, math::Vector<double> mins,
                       math::Vector<double> maxs,
                       double (*f)(math::Vector<double>))
    : min_(mins), max_(maxs), solution_(sol), fitness_function_(f) {
  // std::cout<<"SOL: "<<sol.toString()<<std::endl;
  // std::cout<<"NEW SOL: "<<solution_.toString()<<std::endl;
  n_ = sol.rows() * sol.columns();
}

RnSolution::RnSolution(uint32_t n, math::Vector<double> mins,
                       math::Vector<double> maxs,
                       double (*f)(math::Vector<double>))
    : n_(n), min_(mins), max_(maxs), solution_(math::r(n)),
      fitness_function_(f) {}

RnSolution::RnSolution(math::Vector<double> sol, double min, double max,
                       double (*f)(math::Vector<double>))
    : n_(sol.size()), min_(sol.size(), min), max_(sol.size(), max),
      solution_(sol), fitness_function_(f) {}
RnSolution::~RnSolution() {}

double RnSolution::max(int d) { return max_.at(d); }

double RnSolution::min(int d) { return min_.at(d); }

math::Vector<double> RnSolution::max() { return max_; }

math::Vector<double> RnSolution::min() { return min_; }

math::Vector<double> RnSolution::solution() { return solution_; }

ASolution *RnSolution::neighbour(int i, int j) {
  math::Vector<double> clone = solution_;
  clone.set(solution_.at(j), i);
  clone.set(solution_.at(i), j);
  return new RnSolution(clone, min_, max_, fitness_function_);
}

ASolution *RnSolution::random() {
  std::vector<double> r(n_);
  // math::Vector<double> r(n_);
  for (uint32_t i = 0; i < n_; i++) {
    double x =
        double(rand()) / RAND_MAX * (max_.at(i) - min_.at(i)) + min_.at(i);
    r[i] = x;
  }
  math::Vector<double> m = min_;
  math::Vector<double> M = max_;
  RnSolution *x =
      new RnSolution(math::Vector<double>(n_, r), m, M, fitness_function_);
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
  math::Vector<double> x(n_);
  for (uint32_t i = 0; i < n_; i++) {
    x.set(solution_.at(is[i]), i);
  }
  return new RnSolution(x, min_, max_, fitness_function_);
}

double RnSolution::sub_fitness(int i, int j) { return 0; }
double RnSolution::fitness() { return fitness_function_(solution_); }

int RnSolution::n() { return n_; }

RnSolution *RnSolution::create(math::Vector<double> x) {
  return new RnSolution(x, min_, max_, fitness_function_);
}

std::string RnSolution::to_string() {
  std::stringstream bff;
  bff << "[" << solution_.at(0);
  for (uint32_t i = 1; i < n_; i++) {
    bff << ", " << solution_.at(i);
  }
  bff << "] : " << fitness();
  return bff.str();
}
