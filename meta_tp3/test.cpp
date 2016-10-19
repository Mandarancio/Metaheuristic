#include "tsp.hpp"
#include "sa.hpp"
#include "meta.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#if PLOT
#include "histo.hpp"
#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;
#endif
double std_dev(std::vector<double> vs, double mu){
  
  double avg = 0;
  for (int i = 0 ;i<vs.size();i++)
  {
    avg+=pow((vs[i]-mu),2);
  }
  return sqrt(avg/vs.size());

}
double mean(std::vector<double> vs)
{
  double avg = 0;
  for (int i = 0 ;i<vs.size();i++)
  {
    avg+=vs[i];
  }
  return avg/vs.size();
}

int main(int argc, char * argv[])
{
  if (argc<2)
  {
    std::cout<<"test DAT_FILE"<<std::endl;
    return -1;
  }
  int N =1;
  
  if (argc==3)
  {
    N = atoi(argv[2]);
  }
  std::string path(argv[1]);
  srand(time(NULL));
  std::vector<double> best_fit;

  double min_fit=10000;
  tsp::Solution * min_sol = NULL;
  for (int i = 0;i<N;i++)
  {
    std::cout<<"\r"<<i<<"/"<<N<<std::flush;
    tsp::Solution *a= tsp::randomFromFile(path,true);
    sa::Annealing meta(a);
    meta::ASolution * best = meta.run();
    double fitness = best->fitness();
    best_fit.push_back(fitness);
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
  double avg = mean(best_fit);
  double sigma = std_dev(best_fit,avg);
  std::cout<<"\r"<<N<<"/"<<N<<std::endl;
  std::cout<<"Best fitness: "<<min_fit<<std::endl;
  std::cout<<"Mean: "<<avg<<std::endl;
  std::cout<<"Deviation: "<<sigma<<std::endl;
#if PLOT
  plt::plot({0.,N-1.},{avg,avg},"r--");
  plt::plot(best_fit,"x-");
  if (N>10)
  {
  //  std::vector<double> * xy=hh::histo(best_fit,10,false);
  //  plt::plot(xy[1],xy[0]);
  }
  plt::plot({0.,N-1.},{avg-sigma,avg-sigma},"g--");
  plt::plot({0.,N-1.},{avg+sigma,avg+sigma},"g--");
  plt::figure();
  std::vector<double> x,y;
  for (int i=0;i<min_sol->n();i++)
  {
    x.push_back(min_sol->cities()[i].x());
    y.push_back(min_sol->cities()[i].y());
  }
  x.push_back(x[0]);
  y.push_back(y[0]);
  plt::plot(x,y,"o-");
  plt::show();
#endif
  return 0;
}
