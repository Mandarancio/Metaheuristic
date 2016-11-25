#ifndef RSOLUTION_HPP
#define RSOLUTION_HPP
#include "matrix.hpp"
#include "meta.hpp"
namespace meta {
class RnSolution : public ASolution {
public:
  RnSolution(math::Vector<double> sol, math::Vector<double> mins,
             math::Vector<double> maxs, double (*f)(math::Vector<double>));
  RnSolution(uint32_t n, math::Vector<double> mins, math::Vector<double> maxs,
             double (*f)(math::Vector<double>));
  ~RnSolution();
  double max(int d);
  double min(int d);
  math::Vector<double> max();
  math::Vector<double> min();
  math::Vector<double> solution();
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
  RnSolution *create(math::Vector<double> x);

private:
  uint32_t n_;
  math::Vector<double> min_;
  math::Vector<double> max_;
  math::Vector<double> solution_;
  double (*fitness_function_)(math::Vector<double>);
};
};
#endif
