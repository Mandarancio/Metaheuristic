#include "tsp.hpp"
#include "annealing.hpp"
#include "greedy.hpp"
#include "meta.hpp"
#include "exmath.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <cstring>

#include "histo.hpp"
#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;

void run(meta::AMeta * meta, std::string path, int N)
{
  std::vector<double> best_fit;
  std::vector<double> iters;
  
  double min_fit=10000;
  double t0= 0.0;
  tsp::Solution * min_sol = NULL;
  std::cout<<"\n\033[31;1m"<<meta->name()<<"\033[0m\n\n";
  for (int i = 0;i<N;i++)
  {
    
    std::cout<<"\r"<<i<<"/"<<N<<std::flush;
    tsp::Solution *a= tsp::randomFromFile(path,true);
    meta->reset(a);
    meta::ASolution * best = meta->run();
    double fitness = best->fitness();
    best_fit.push_back(fitness);
    iters.push_back(meta->iters());
    if (fitness<min_fit)
    {
      delete min_sol;
      min_sol=dynamic_cast<tsp::Solution*>(best);
      min_fit=fitness;
    }else {
      delete best;
    }
    //delete a;        
  }
  double avg = math::mean(best_fit);
  double sigma = math::sigma(best_fit,avg);
  double min_it = *std::min_element(iters.begin(),iters.end());
  double max_it = *std::max_element(iters.begin(),iters.end());
  std::cout<<"\r\033[1m"<<N<<"/"<<N<<std::endl;
  std::cout<<"Best fitness: \033[0m"<<min_fit<<std::endl;
  std::cout<<"\033[1mMean: \033[0m"<<avg<<std::endl;
  std::cout<<"\033[1mDeviation: \033[0m"<<sigma<<std::endl;
  plt::figure();
  double simple_x[]={0,N-1.};
  double s_avg[]={avg,avg};
  double s_n_sigm[]={avg-sigma,avg-sigma};
  double s_p_sigm[]={avg+sigma,avg+sigma};
  plt::plot(simple_x,s_avg,"r--");
  plt::named_plot("Fitness found",best_fit,"x-");
  plt::plot(simple_x,s_n_sigm,"g--");
  plt::plot(simple_x,s_p_sigm,"g--");
  if (N>10)
  {
    std::vector<double> * xy=hh::histo(best_fit,15);
    plt::named_plot("Distribution",xy[1],xy[0],"r-");
    double alpha = *std::max_element(xy[1].begin(),xy[1].end());
    double min_x = *std::min_element(xy[0].begin(),xy[0].end());
    double max_x = *std::max_element(xy[0].begin(),xy[0].end());
    double dx = max_x-min_x;
    min_x-=dx/10.;
    max_x+=dx/10.;
    std::vector<double> x=math::lin_space(min_x,max_x);
    std::vector<double> y = math::std_dist(alpha,avg,sigma,x);
    plt::named_plot("Fit",y,x,"r:");
    double min_y =min_fit;
    double max_y =*std::max_element(best_fit.begin(),best_fit.end());
    std::vector<double> s_iters = math::scale(iters,min_y,max_y);
    plt::named_plot("Iterations",s_iters,"g:");
  }
  plt::xlabel("t");
  plt::ylabel("fitness");

  plt::legend();
  plt::figure();
  std::vector<double> x,y;
  for (int i=0;i<min_sol->n();i++)
  {
    x.push_back(min_sol->cities()[i].x());
    y.push_back(min_sol->cities()[i].y());

  }
  x.push_back(x[0]);
  y.push_back(y[0]);
  plt::named_plot("Solution",x,y,"o-");
  double *xlims = plt::xlim();
  double *ylims = plt::ylim();
  double xrange= xlims[1]-xlims[0];
  plt::xlim(xlims[0]-0.05*xrange,xlims[1]+0.05*xrange);
  plt::ylim(ylims[0]-0.05*xrange,ylims[1]+0.05*xrange);
  if (min_sol->n()<=20)
  {
    
    for (int i=0;i<min_sol->n();i++)
    {
      plt::annotate(min_sol->cities()[i].name(),x[i]-0.02*xrange,y[i]+0.02*xrange);
    }
  }
  plt::legend();
}

int main(int argc, char * argv[])
{
  if (argc!=3)
  {
    std::cout<<"test DAT_FILE N_TEST"<<std::endl;
    return -1;
  }
  int N = atoi(argv[2]);
  
  std::string path(argv[1]);
  srand(time(NULL));
  sa::Annealing * meta_1 = new sa::Annealing(NULL);
  greedy::Greedy * meta_2 = new greedy::Greedy(NULL);
  run(meta_1,path,N);
  run(meta_2,path,N);
  plt::show();
  
  return 0;
}
