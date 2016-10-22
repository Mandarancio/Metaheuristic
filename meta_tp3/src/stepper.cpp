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

void save(meta::ASolution * s, double t, std::string out);

int main(int argc, char * argv[])
{
   if (argc!=3)
  {
    std::cout<<"test DAT_FILE OUTPUT_FOLDER"<<std::endl;
    return -1;
  }
  
  srand(time(NULL));
  
  std::string path(argv[1]);
  std::string out_path(argv[2]);
  
  tsp::Solution *a= tsp::randomFromFile(path,true);
  sa::Annealing * meta = new sa::Annealing(a);
  meta::ASolution * old = meta->oSolution()->clone();
  double t=meta->ti();
  int done = 0;
  double f = old->fitness();
  while (t>1e-3 && done<3)
  {
    std::cout<<"T: "<<t<<std::endl;
    save(old,t,out_path);
    meta::ASolution * s= meta->step(old);
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
//  plt::legend();
  plt::show();
  return 0;
}


void save(meta::ASolution * s, double t, std::string out)
{
//  plt::figure();

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
//  plt::named_plot("T="+std::to_string(t),x,y,"o-");
  plt::named_plot("T="+std::to_string(t),x,y,"o-");
//  plt::title("T="+std::to_string(t));
  plt::save(out+"fig_"+std::to_string(t)+".png");

  plt::close();
}
