#ifndef GREEDY_H
#define GREEDY_H
#include "meta.hpp"

namespace greedy{
  class Greedy: public meta::AMeta
  {
  public:
    Greedy(meta::ASolution * start);
    virtual meta::ASolution * step(meta::ASolution * sol);
    virtual meta::ASolution * run();
    virtual void reset(meta::ASolution * startSol);
  private:
    int index_;
  };
};

#endif
