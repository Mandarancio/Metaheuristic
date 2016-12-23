#ifndef GENETICALG_HPP
#define GENETICALG_HPP
#include "matrix.hpp"
#include <cstdint>
#include <string>
#include <vector>

// namespace eig = Eigen;

namespace GA {
struct limits {
  double min;
  double max;
};

math::Matrix<bool> double2bits(double f, const uint32_t n, limits lim);
double bits2double(math::Matrix<bool> bits, limits lim);

class Element {
public:
  Element(math::Matrix<bool> value, limits lim, double (*f)(double, double));

  Element(double v1, double v2, uint32_t bits, limits lim,
          double (*f)(double, double));
  Element *clone();
  ~Element();

  double fitness();
  double *values();
  const math::Matrix<bool> bitValues() const;

  void mutate(double p);

private:
  math::Matrix<bool> value_;
  limits limits_;
  uint32_t nbits_;
  double (*fitness_function)(double, double);
};

class GeneticAlgorithm {
public:
  GeneticAlgorithm(uint32_t bits, uint32_t population, uint32_t evals,
                   double pcrossover, double pmutation, limits lim,
                   double (*f)(double, double));

  Element *best(double &f);
  void step();
  Element *run();
  ~GeneticAlgorithm();

private:
  void clear_old();
  std::pair<Element *, Element *>
  crossover(std::pair<Element *, Element *> parents);
  void selection();
  void crossover();
  void mutation();
  Element *best(std::vector<Element *>);
  Element *worst(std::vector<Element *>, int &);
  std::vector<Element *> population_;
  uint32_t bits_;
  uint32_t population_size_;
  uint32_t evals_;
  double pcrossover_;
  double pmutation_;
  uint32_t tsize_;
  limits limits_;
  double (*fitness_function)(double, double);
};
};

#endif
