#include "sa.hpp"
#include <cstdlib>
#include <cmath>

using namespace sa;

Annealing::Annealing(meta::ASolution * startSolution):
  zero_conf_(startSolution), t0_(0), ti_(0), T_(0)
{
  computeT0();
}

Annealing::~Annealing()
{
  delete zero_conf_;
}

meta::ASolution * Annealing::run()
{
  bool condition = false;
  ti_=t0_;
  meta::ASolution * old = zero_conf_->neighbour(0,0);
  meta::ASolution * current = NULL;
  int accepted = 0;
  int attempted = 0;
  T_=0;
  int n = old->n();
  int no_counter = 0;
  while (!condition)
  {
    current = old->rand_neighbour();
    double fitness = current->fitness();
    attempted ++;
    double de = fitness-old->fitness();
    if (de<=0 || rand()<=exp(-de/ti_))
    {
      accepted++; 
      delete old;
      old=current;
    }else{
      delete current; 
    }
    T_++;
    if (accepted >=12*n || attempted>=100*n)
    {
      ti_=0.95*ti_;
      
      if (accepted ==0   || ti_<1e-8) 
      {
        condition = true;
      }
      accepted=0;
      attempted=0;
    }
    
  }
  return old;
}

meta::ASolution * Annealing::oConfiguration()
{
  return zero_conf_;
}

double Annealing::t0()
{
  return t0_;
}

void Annealing::computeT0()
{
  while (t0_<=0)
  {
    meta::ASolution * old= zero_conf_->neighbour(0,0);
    double delta_e=0;
    int n = old->n();
    for (int i =0 ;i<100;i++){
      meta::ASolution * curr = old->rand_neighbour();
      delta_e+= pow(curr->fitness()-old->fitness(),2);
      delete old;
      old = curr;
    }
    delete old;
    delta_e = sqrt(delta_e/100);
    t0_=10.0*-delta_e/log(0.5);
    if (t0_<0)
    {
      meta::ASolution * sol = zero_conf_->random();
      delete zero_conf_;
      zero_conf_ = sol;
    }
  }
  ti_=t0_;
}

int Annealing::T()
{
  return T_;
}
double Annealing::tf()
{
  return ti_;
}

