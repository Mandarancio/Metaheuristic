#ifndef PSO_HPP
#define PSO_HPP

#include "meta.hpp"
#include "rsolution.hpp"

#include <vector>

namespace pso {
template <typename T> class Particle {
public:
  Particle(T *position, double omega, double c1, double c2, double vmax);

  ~Particle();
  double current_fitness();
  T *current_position();
  double best_fitness();
  T *best_position();
  double move(T *group_best);
  eig::VectorXd speed();
  eig::VectorXd pos() const;

private:
  double best_fitness_;
  eig::VectorXd bounce(eig::VectorXd p);
  eig::VectorXd limit(eig::VectorXd s);
  T *position_;
  eig::VectorXd speed_;
  eig::VectorXd pos_;
  T *particle_best_;
  double omega_, c1_, c2_, vmax_;
};
template <typename T> class PSO : public meta::AMeta {
public:
  PSO(T *startSolution, int n_particle, int tmax, double omega, double c1,
      double c2, double vmax);
  ~PSO();
  virtual meta::ASolution *step(meta::ASolution *sol);
  virtual meta::ASolution *run();
  virtual void reset(meta::ASolution *sol);
  std::vector<Particle<T> *> particles();

private:
  double omega_, c1_, c2_, vmax_;
  int n_particles_;
  int tmax_;
  double bf_;
  std::vector<Particle<T> *> particles_;
};
};

#endif
