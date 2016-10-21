#ifndef SA_HPP
#define SA_HPP
#include "meta.hpp"

namespace sa{
  class Annealing: public meta::AMeta
  {
  public:
    Annealing(meta::ASolution * startSolution);
    virtual meta::ASolution * run();
    virtual void reset(meta::ASolution * startSol);
    double t0();
    double tf();
  private:
    void computeT0();
    double t0_;
    double ti_;
  };
};

#endif
