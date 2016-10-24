#include "tsp.hpp"
#include "annealing.hpp"
#include "meta.hpp"

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <cstring>

#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;

void plot(meta::ASolution * s, double t, double alpha=0.1,std::string style="o-");

int main(int argc, char * argv[])
{
   if (argc!=2)
  {
    std::cout<<"test DAT_FILE"<<std::endl;
    return -1;
  }
  
  srand(time(NULL));
  
  std::string path(argv[1]);
  
  tsp::Solution *a= tsp::randomFromFile(path,true);
 
  
  sa::Annealing * meta = new sa::Annealing(a);
  meta::ASolution * old = meta->oSolution()->clone();
  double t=meta->ti();
  int done = 0;
  double f = old->fitness();
  while (t>1e-3 && done<1)
  {
    std::cout<<"T: "<<t<<std::endl;
    plot(old,t);
    meta::ASolution * s= meta->step(old);
    meta->step_down_t();
    t=meta->ti();
    if (s)
    {
      double nf = s->fitness();
      if (nf==f)
      {
        done++;
      }
      f=nf; 
      delete old;
      old=s;
      
    }
    else
    {
      done++;
    }
  }
  std::cout<<"T: "<<t<<std::endl;
  plot(old,t,1,"ko-");
  plt::title("f="+std::to_string(old->fitness()));

  plt::show();
  return 0;
}


void plot(meta::ASolution * s, double t, double alpha,std::string style)
{

  double fitness=s->fitness();
  std::vector<double> x,y;
  tsp::Solution* min_sol = dynamic_cast<tsp::Solution *> (s); 
  for (int i=0;i<min_sol->n();i++)
  {
    x.push_back(min_sol->cities()[i].x());
    y.push_back(min_sol->cities()[i].y());
  }
  x.push_back(x[0]);
  y.push_back(y[0]);
  plt::named_plot("T="+std::to_string(t),x,y,style,alpha);

}
