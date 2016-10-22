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
meta::ASolution * Annealing::step(meta::ASolution * sol)
{

  meta::ASolution * old = sol->clone();
  meta::ASolution * current = NULL;

  double old_fitness = old->fitness();
  int attempted = 0;
  int accepted = 0;
  int n = old->n();
  while (! (accepted >=1 || attempted>=100*n))
  {
    attempted ++;
    iters_++;
    current = old->rand_neighbour();
    double fitness = current->fitness();
    double de = fitness-old_fitness;
     if (de<=0 || rand()<=exp(-de/ti_))
    {
      accepted++; 
      delete old;
      old=current;
      old_fitness = fitness;
    }
    else
    {
      delete current; 
    }   
  }
  if (accepted==0)
  {
    delete old;
  }
  ti_=0.9*ti_;
  
  return accepted > 0 ? old : NULL;
}

meta::ASolution * Annealing::run()
{

  ti_=t0_;
  meta::ASolution * old = startSolution_->clone();
  double last_fitness = old->fitness();
  int done = 0;
  while (ti_>1e-3 && done <3)
  {
    meta::ASolution *s= this->step(old);
    if (s==NULL)
    {
      done++;
    }
    else
    {
      double f = s->fitness();
      delete old;
      old  = s;
     
      if (f == last_fitness)
      {
        done++;
      }  
      last_fitness=f;
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
    meta::ASolution * old= startSolution_->clone();
    double delta_e=0;
    int n = old->n();
    for (int i =0 ;i<100;i++){
      meta::ASolution * curr = old->rand_neighbour();
      delta_e+= curr->fitness()-old->fitness();
      delete old;
      old = curr;
    }
    delete old;
//    delta_e = sqrt(delta_e/100);
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


double Annealing::ti()
{
  return ti_;
}

