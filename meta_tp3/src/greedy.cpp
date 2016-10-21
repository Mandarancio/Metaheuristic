#include "greedy.hpp"

using namespace greedy;

Greedy::Greedy(meta::ASolution * start): 
  meta::AMeta(start,"Greedy")
{
}

meta::ASolution * Greedy::run()
{
  double fitness = startSolution_->fitness();
  meta::ASolution * sol = startSolution_->neighbour(0,0);
  while (true)
  { 
    iters_++;
    std::vector<meta::ASolution *> neighbours = startSolution_->neighbours();
    meta::ASolution * best = NULL;
    double best_fit = fitness;
    for (int i=0;i<neighbours.size();i++)
    {
      double fit= neighbours[i]->fitness();
      if (fit<best_fit)
      {
        if (best)
        {
          delete best;  
        }
        best_fit= fit;
        best = neighbours[i];
      }else{
        delete neighbours[i];
      }
    }
    if (!best)
    {
      return sol; 
    }else
    {
      delete sol;
      sol = best;
      fitness= best_fit;
    }
  }
  return sol;
}
