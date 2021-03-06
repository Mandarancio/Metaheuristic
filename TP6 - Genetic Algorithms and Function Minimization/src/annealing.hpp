#ifndef SA_HPP
#define SA_HPP
#include "meta.hpp"

namespace sa{
  class Annealing: public meta::AMeta
  {
  public:
    Annealing(meta::ASolution * startSolution, int max_perm = 100, int max_accepted = 12);
    virtual meta::ASolution * run();
    virtual meta::ASolution * step(meta::ASolution * sol);
    virtual void reset(meta::ASolution * startSol);
    void step_down_t();
    void set_ti(double t);
    double t0();
    double ti();
  private:
    void computeT0();
    double t0_;
    double ti_;
    int max_perm_;
    int max_accepted_;
  };
};

#endif
