#ifndef PSO_HPP
#define PSO_HPP


#include "meta.hpp"
#include <vector>

namespace pso
{

class Particle
{
public:
  Particle(meta::RnSolution * position,double omega, double c1, double c2,double vmax);
  
  ~Particle();
  double current_fitness();
  meta::RnSolution * current_position();
  double best_fitness();
  meta::RnSolution * best_position();
  double move(meta::RnSolution * group_best);
  std::vector<double> speed();
private:  
  std::vector<double> bounce(std::vector<double> p);
  std::vector<double> limit(std::vector<double> s);
  meta::RnSolution *position_;
  std::vector<double> speed_;
  meta::RnSolution * particle_best_;
  double omega_, c1_,c2_, vmax_;
};

class PSO: public meta::AMeta
{
public:
  PSO(meta::RnSolution * startSolution, int n_particle, int tmax, double omega, double c1, double c2, double vmax);
  ~PSO();
  virtual meta::ASolution * step(meta::ASolution * sol);
  virtual meta::ASolution * run();
  virtual void reset(meta::ASolution * sol);
  std::vector<Particle*> particles();
private:
  double omega_,c1_,c2_,vmax_;
  int n_particles_;
  int tmax_;
  std::vector<Particle*> particles_;
};

};

#endif
