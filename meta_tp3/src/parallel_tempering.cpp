#include "tsp.hpp"
#include "annealing.hpp"
#include "meta.hpp"
#include "exmath.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MIN(x,y) (x<y? x:y)
#include "histo.hpp"
#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;

void run(std::string path, int nreplica);

int main(int argc, char * argv[])
{
  if (argc!=3)
  {
    std::cout<<"test DAT_FILE N_REPLICA"<<std::endl;
    return -1;
  }

  int NR = atoi(argv[2]);
  std::string path(argv[1]);
  srand(time(NULL));
  run(path,NR);
  plt::show();
  
  return 0;
}

void run(std::string path, int nreplica)
{
  int imax= 200;//5*nreplica+20;//10*nreplica;
  std::vector<sa::Annealing*> metas;
  std::vector<meta::ASolution * > solutions;
  std::vector<double> Bs;
  //Initialize
  double Mt=0;
  for (int i = 0;i<nreplica;i++)
  {
    sa::Annealing *sa=new sa::Annealing(tsp::randomFromFile(path), 12,100);
    solutions.push_back(sa->oSolution());
    metas.push_back(sa);

    if (Mt<sa->t0())
    {
      Mt=sa->t0();
    }
  }

  Mt*=2;
 
  for (int i=0;i<nreplica;i++){
    
    double t = Mt*1/(nreplica-i);
    double b = 1.0/t;
    metas[i]->set_ti(t);

    Bs.push_back(b);
  }
  //Run
  for (int i=0;i<imax;i++)
  { 
    for (int j=0;j<nreplica;j++)
    {
    
      
      meta::ASolution * sol = metas[j]->step(solutions[j]);
      if (sol)
      {
        solutions[j]=sol;
      }
      
    
//    for (int k=0;k<nreplica-1;k++){
      for (int z=0;z<nreplica-1;z++)
      {

        double bi = Bs[z];
        double bj = Bs[z+1];
        double ei = solutions[z]->fitness();
        double ej = solutions[z+1]->fitness();
        double p= MIN(1,exp((bi-bj)*(ei-ej)));
        if (rand()/RAND_MAX<p)
        {

          meta::ASolution * t= solutions[z];
          solutions[z]=solutions[z+1];
          solutions[z+1]=t;
         
        }
      }
    }
  }
  tsp::Solution * min_sol = dynamic_cast<tsp::Solution*>(solutions[0]);
  std::vector<double> x,y;
  for (int i=0;i<min_sol->n();i++)
  {
    x.push_back(min_sol->cities()[i].x());
    y.push_back(min_sol->cities()[i].y());
  }
  std::cout<<"\033[1mFitness: \033[0m"<<min_sol->fitness()<<std::endl;
  x.push_back(x[0]);
  y.push_back(y[0]);
  plt::plot(x,y,"o-");
}
