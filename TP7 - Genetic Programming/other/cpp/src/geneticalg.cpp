#include "geneticalg.hpp"
#include "exmath.hpp"
#include <cmath>

using namespace GA;

math::Matrix<bool> GA::double2bits(double f, const uint32_t n, limits lim) {
  math::Matrix<bool> bits(n, 1, 0);
  if (f < lim.min) {
    return math::Matrix<bool>(n, 1, false);
  } else if (f >= lim.max) {
    return math::Matrix<bool>(n, 1, true);
  } else {
    math::Matrix<bool> bits(n, 1, 0);

    double size = pow(2, n);
    double dt = (lim.max - lim.min) / size;
    uint32_t d = round((f - lim.min) / dt);
    uint32_t i = 0;
    while (d > 0 && i < n) {
      uint32_t bit = d % 2;
      d = d / 2;
      bits[n - i - 1] = bit;
      i++;
    }
  }
  return bits;
}

double GA::bits2double(math::Matrix<bool> bits, limits lim) {
  uint32_t n = bits.rows();
  double size = pow(2, n);
  double dt = (lim.max - lim.min) / size;

  double v = lim.min;
  for (uint32_t i = 0; i < n; i++) {
    uint32_t k = n - i - 1;
    double x = pow(2, k) * bits[i] * dt;
    v += x;
  }

  return v;
}

Element::Element(math::Matrix<bool> value, limits lim,
                 double (*f)(double, double))
    : value_(value), limits_(lim), fitness_function(f) {
  nbits_ = value.rows();
}

Element::Element(double v1, double v2, uint32_t bits, limits lim,
                 double (*f)(double, double))
    : value_(new math::Matrix<bool>(bits, 2)), limits_(lim), nbits_(bits),
      fitness_function(f) {
  // value_ = ;
  math::Matrix<bool> a1 = double2bits(v1, bits, lim);
  math::Matrix<bool> a2 = double2bits(v2, bits, lim);
  for (uint32_t i = 0; i < bits; i++) {
    value_.set(a1[i], i, 0);
    value_.set(a2[i], i, 1);
  }
}

Element::~Element() {}

double Element::fitness() {
  double *values = this->values();
  double f = fitness_function(values[0], values[1]);
  delete[] values;
  return f;
}

Element *Element::clone() {
  // double *v = values();
  return new Element(value_, limits_, fitness_function);
}
double *Element::values() {
  double *v = new double[2];
  v[0] = bits2double(this->value_.column(0), limits_);
  v[1] = bits2double(this->value_.column(1), limits_);
  return v;
}
const math::Matrix<bool> Element::bitValues() const { return value_; }

void Element::mutate(double p) {
  for (uint32_t i = 0; i < value_.size(); i++) {
    double r = math::r();
    if (r <= p) {
      value_[i] = !value_[i]; // = !v;
    }
  }
}

GeneticAlgorithm::GeneticAlgorithm(uint32_t bits, uint32_t population,
                                   uint32_t evals, double pcrossover,
                                   double pmutation, limits lim,
                                   double (*f)(double, double))
    : bits_(bits), population_size_(population), evals_(evals),
      pcrossover_(pcrossover), pmutation_(pmutation), limits_(lim),
      fitness_function(f) {
  double dt = lim.max - lim.min;
  for (unsigned int i = 0; i < population_size_; i++) {
    double a = math::r() * dt + lim.min;
    double b = math::r() * dt + lim.min;
    population_.push_back(new Element(a, b, bits_, limits_, fitness_function));
  }
  tsize_ = 5;
}

GeneticAlgorithm::~GeneticAlgorithm() {
  for (uint32_t i = 0; i < population_.size(); i++) {
    delete population_[i];
  }
  population_.clear();
}

void GeneticAlgorithm::step() {
  Element *e = best(population_)->clone();
  selection();
  crossover();
  mutation();
  // delete
  int i = 0;
  Element *x = worst(population_, i);
  population_[i] = e;
  delete x;
}

std::pair<Element *, Element *>
GeneticAlgorithm::crossover(std::pair<Element *, Element *> parents) {
  if (math::r() <= pcrossover_) {
    Element *a =
        new Element(parents.first->values()[0], parents.second->values()[1],
                    bits_, limits_, fitness_function);
    Element *b =
        new Element(parents.second->values()[0], parents.first->values()[1],
                    bits_, limits_, fitness_function);
    return std::pair<Element *, Element *>(a, b);
  }
  return std::pair<Element *, Element *>(parents.first->clone(),
                                         parents.second->clone());
}

Element *GeneticAlgorithm::run() {
  for (uint32_t i = 0; i < evals_; i++) {
    step();
  }
  return this->best(population_);
  // return best;
}

Element *GeneticAlgorithm::best(double &f) {
  Element *b = best(population_);
  f = b->fitness();
  return b;
}

void GeneticAlgorithm::selection() {
  std::vector<Element *> new_pop;
  for (uint32_t i = 0; i < population_size_; i++) {
    std::vector<Element *> tournament;
    for (uint32_t j = 0; j < tsize_; j++) {
      uint32_t e = math::rint(0, population_size_);
      tournament.push_back(population_[e]);
    }

    new_pop.push_back(this->best(tournament)->clone());
    tournament.clear();
  }
  clear_old();
  population_ = new_pop;
}

void GeneticAlgorithm::crossover() {
  std::vector<Element *> new_pop;
  for (uint32_t i = 0; i < population_size_; i += 2) {
    std::pair<Element *, Element *> parents(population_[i], population_[i + 1]);
    std::pair<Element *, Element *> children = crossover(parents);
    new_pop.push_back(children.first);
    new_pop.push_back(children.second);
  }
  clear_old();
  population_ = new_pop;
}

void GeneticAlgorithm::mutation() {
  for (uint32_t i = 0; i < population_size_; i++) {
    population_[i]->mutate(pmutation_);
  }
}

void GeneticAlgorithm::clear_old() {
  for (uint32_t i = 0; i < population_size_; i++) {
    delete population_[i];
  }
  population_.clear();
}

Element *GeneticAlgorithm::best(std::vector<Element *> set) {
  Element *b = set[0];
  double f = b->fitness();
  for (uint32_t i = 1; i < set.size(); i++) {
    double t = set[i]->fitness();
    if (f > t) {
      f = t;
      b = set[i];
    }
  }
  return b;
}

Element *GeneticAlgorithm::worst(std::vector<Element *> set, int &x) {
  Element *b = set[0];
  x = 0;
  double f = b->fitness();
  for (uint32_t i = 1; i < set.size(); i++) {
    double t = set[i]->fitness();
    if (f < t) {
      f = t;
      b = set[i];
      x = i;
    }
  }
  return b;
}
