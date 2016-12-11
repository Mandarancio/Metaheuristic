#ifndef RSOLUTION_HPP
#define RSOLUTION_HPP
#include "meta.hpp"
#include <eigen3/Eigen/Dense>

namespace eig = Eigen;

namespace meta {
class RnSolution : public ASolution {
public:
  RnSolution(eig::VectorXd sol, eig::VectorXd mins, eig::VectorXd maxs,
             double (*f)(eig::VectorXd));
  RnSolution(uint32_t n, eig::VectorXd mins, eig::VectorXd maxs,
             double (*f)(eig::VectorXd));
  RnSolution(eig::VectorXd sol, double min, double max,
             double (*f)(eig::VectorXd));
  ~RnSolution();
  double max(int d);
  double min(int d);
  eig::VectorXd max();
  eig::VectorXd min();
  eig::VectorXd solution();
  virtual ASolution *neighbour(int i, int j);
  virtual ASolution *random();
  virtual ASolution *rand_neighbour();
  virtual ASolution *sub_solution(int i, int j);
  virtual double sub_fitness(int i, int j);
  virtual double fitness();
  virtual std::vector<ASolution *> neighbours();
  virtual int n();
  virtual std::string to_string();
  virtual ASolution *create(std::vector<int> is);
  virtual RnSolution *create(eig::VectorXd x);

private:
  uint32_t n_;
  eig::VectorXd min_;
  eig::VectorXd max_;
  eig::VectorXd solution_;
  double (*fitness_function_)(eig::VectorXd);
};
};
#endif
