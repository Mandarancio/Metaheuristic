#ifndef SA_HPP
#define SA_HPP
#include "meta.hpp"

namespace sa{
  class Annealing{
  public:
    Annealing(meta::ASolution * startSolution);
    ~Annealing();
    meta::ASolution * run();
    meta::ASolution * oConfiguration();
    double t0();
    int T();
    double tf();
  private:
    void computeT0();
    double t0_;
    meta::ASolution * zero_conf_;
    double ti_;
    int T_;
  };
};

#endif
