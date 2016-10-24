#include "annealing.hpp"
#include <cstdlib>
#include <cmath>

#include <iostream>
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


  double old_fitness = old->fitness();
  int attempted = 0;
  int accepted = 0;
  int n = old->n();
  while (!(accepted >=12*n || attempted>=100*n))
  {
    attempted ++;
    iters_++;
    int i = rand()%n;
    int j = rand()%n;
    
    double de = old->delta_fitness(i,j);
    double r = ((double) rand() / (RAND_MAX)) ;
    if (de<=0 || r<=exp(-de/ti_))
    {
      accepted++; 
      meta::ASolution * current = old->neighbour(i,j);
      delete old;
      old=current;
      old_fitness = old->fitness();
    }
  
  }


  if (accepted==0)
  {
    delete old;
  }
  return accepted > 0 ? old : NULL;
}

void Annealing::step_down_t()
{
  ti_=0.9*ti_;
}

meta::ASolution * Annealing::run()
{

  ti_=t0_;
  meta::ASolution * old = startSolution_->clone();
  double last_fitness = old->fitness();
  int done = 0;
  while (ti_>1e-3 && done <3)
  //change done<N if needed to change precision
  {
    meta::ASolution *s= this->step(old);
    step_down_t();
    if (s==NULL)
    {
      done++;
    }
    else
    {
      double f = s->fitness();
      delete old;
      old  = s;
     
//      if (f == last_fitness)
//      {
//        done++;
//      }  
//      last_fitness=f;
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
    int N = 100;
    double delta_e=0;
    double f = startSolution_->fitness();
    int n = startSolution_->n();
    for (int i =0 ;i<N;i++){
      meta::ASolution * curr = startSolution_->rand_neighbour();
      delta_e+=curr->fitness()-f;
      delete curr;
    }
    delta_e/=N;
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

void Annealing::set_ti(double t)
{
  ti_=t;
}

double Annealing::ti()
{
  return ti_;
}

