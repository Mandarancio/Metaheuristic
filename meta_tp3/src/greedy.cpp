#include "greedy.hpp"

using namespace greedy;

Greedy::Greedy(meta::ASolution * start): 
  meta::AMeta(start,"Greedy")
{
  index_ = 1;
}

void Greedy::reset(meta::ASolution * startSol)
{
  meta::AMeta::reset(startSol);
  index_=1;
}

meta::ASolution *  Greedy::step(meta::ASolution * sol)
{
  
  meta::ASolution * next =  sol->clone();
  double best_fit =0;

  for (int i =0;i<sol->n()-1;i++)
  {
    for (int j=i+1;j<sol->n();j++)
    {
      iters_++;
      double fit = next->delta_fitness(i,j);
      if (fit<best_fit)
      {
        meta::ASolution * s = sol->neighbour(i,j);
        delete next;
        best_fit = fit;
        next= s;
      }
    }
  }
  
  if (best_fit==0 or iters_>300*sol->n()){
    return NULL;
  }
  return next;
}

meta::ASolution * Greedy::run()
{
  index_=1;
  double fitness = startSolution_->fitness();
  meta::ASolution * sol = startSolution_->clone();
  while (true)
  { 
    meta::ASolution * next = step(sol);
    if (!next)
    {
      return sol;
    }else
    {
      delete sol;
      sol = next;
    }
  }
  return sol;
}
