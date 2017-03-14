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

void plot(meta::ASolution * s, double t, double alpha=1.0,std::string style="o-");
void save_plot(std::string path);
void help();


int main(int argc, char * argv[])
{
   if (argc<2)
  {
    help();
    return -1;
  }
  
  bool save = false;
  std::string out_dir="";
  
  if (strcmp(argv[1],"--help")==0)
  {
    help();
    return 0;
  }
  
  for (int i = 2;i<argc;i++)
  {
    if (strcmp(argv[i],"--help")==0)
    {
      help();
      return 0;
    }else if (strcmp(argv[i],"--save")==0 && i<argc-1)
    {
      save= true;
      out_dir = std::string(argv[i+1]);
      i++;
    }
  }
  
  srand(time(NULL));
  
  std::string path(argv[1]);
  
  tsp::Solution *a= tsp::randomFromFile(path,true);

  sa::Annealing * meta = new sa::Annealing(a);
  meta::ASolution * old = meta->oSolution()->clone();
  double t=meta->ti();
  int done = 0;
  double alpha = save?1.0:0.1;
  double f = old->fitness();
  while (t>1e-3 && done<1)
  {
    std::cout<<"T: "<<t<<std::endl;
    plot(old,t,alpha);
    if (save)
    {  
      plt::title("f="+std::to_string(old->fitness()));
      save_plot(out_dir+"/sol_"+std::to_string(t)+".png");
    }
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
  plt::title("f="+std::to_string(old->fitness()));
  
  if (!save)
  {
    plot(old,t,1,"ko-");
  }else{
    plot(old,t,1.0);
    plt::save(out_dir+"/"+std::to_string(t)+".png");
  }
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

void save_plot(std::string path)
{
  plt::save(path);
  plt::close();
}

void help()
{
    std::cout<<"test DAT_FILE [OPTIONS]"<<std::endl
    <<" --save OUT_FOLDER : save each step plot"<<std::endl
    <<" --help : show this help"<<std::endl;
}
