#ifndef SA_HPP
#define SA_HPP
#include "meta.hpp"

namespace sa{
  class Annealing: public meta::AMeta
  {
  public:
    Annealing(meta::ASolution * startSolution);
    virtual meta::ASolution * run();
    virtual meta::ASolution * step(meta::ASolution * sol);
    virtual void reset(meta::ASolution * startSol);
    double t0();
    double ti();
  private:
    void computeT0();
    double t0_;
    double ti_;
  };
};

#endif
