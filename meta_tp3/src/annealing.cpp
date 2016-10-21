#include "annealing.hpp"
#include <cstdlib>
#include <cmath>

using namespace sa;

Annealing::Annealing(meta::ASolution * startSolution):
  t0_(0), ti_(0), meta::AMeta(startSolution,"Simulated Annealing")
{
  if (startSolution_)
  {
    computeT0();
  }
}


meta::ASolution * Annealing::run()
{
  bool condition = false;
  ti_=t0_;
  meta::ASolution * old = startSolution_->neighbour(0,0);
  meta::ASolution * current = NULL;
  int accepted = 0;
  int attempted = 0;
  int n = old->n();
  int no_counter = 0;
  int done = 0;
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
    iters_++;
    if (accepted >=12*n || attempted>=100*n)
    {
      ti_=0.95*ti_;
      
      if ((accepted ==0  && done==10) || ti_<1e-4) 
      {
        condition = true;
      }else {
        done = accepted==0 ? done + 1 : 0;
      }
      accepted=0;
      attempted=0;
    }
    
  }
  return old;
}


void Annealing::reset(meta::ASolution * startSol)
{
  meta::AMeta::reset(startSol);
  computeT0();  
}

double Annealing::t0()
{
  return t0_;
}

void Annealing::computeT0()
{
  while (t0_<=0)
  {
    meta::ASolution * old= startSolution_->neighbour(0,0);
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
    t0_=-delta_e/log(0.5);
    if (t0_<0)
    {
      meta::ASolution * sol = startSolution_->random();
      delete startSolution_;
      startSolution_ = sol;
    }
  }
  ti_=t0_;
}


double Annealing::tf()
{
  return ti_;
}

