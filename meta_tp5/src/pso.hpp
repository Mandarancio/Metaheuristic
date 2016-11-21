#ifndef PSO_HPP
#define PSO_HPP

#include "meta.hpp"

namespace pso
{

class Particle
{
public:
  Particle(meta::RnSolution * position, std::vector <double> speed);
  double current_fitness();
  meta::RnSolution * current_position();
  double best_fitness();
  meta::RnSolution * best_position();
  double move(meta::RnSolution * group_best);
private:  
  meta::RnSolution *position_;
  std::vector<double> speed_;
  meta::RnSolution * partical_best_;
};

class PSO: : public meta::AMeta
{
public:
  PSO(meta::ASolution * startSolution);
  ~PSO();
  
  virtual meta::ASolution * step(meta::ASolution * sol);
  virtual meta::ASolution * run();
  virtual void reset(meta::ASolution * sol);
};

};

#endif
