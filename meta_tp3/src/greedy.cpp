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
  if (index_==sol->n()-1)
  {
    return NULL;
  } 
  iters_++;
  meta::ASolution * next =  sol->clone();
  double best_fit = next->fitness();

  for (int i =index_+1;i<sol->n();i++)
  {
    iters_++;
    meta::ASolution * s = sol->neighbour(index_,i);
    double fit = s->fitness();
    if (fit<best_fit)
    {
      delete next;
      best_fit = fit;
      next= s;
    }
    else
    {
      delete s;
    }
  }
  index_++;
  return next;
}

meta::ASolution * Greedy::run()
{
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
