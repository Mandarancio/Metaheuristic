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

#if !NO_PLOT
#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;
#endif

double run(std::string path, int nreplica);

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
  std::vector<double> fs;
  double average = 0.;
  double min = 1000000;
  int t=clock();
  for (int i =0;i<20;i++)
  { 
    double f=run(path,NR);
    average+=f;
    if (f<min)
    {
      min=f;
    }
    fs.push_back(f);
  }
  t = clock() - t;
  int millit = round(1000.*((double)t)/CLOCKS_PER_SEC);
  std::cout<<"Time: "<<millit<<"ms"<<std::endl;
  average/=20;
  std::cout<<"Average f:"<<average<<std::endl;
  std::cout<<"Best f: "<<min<<std::endl;
  std::cout<<"Sigma: "<<math::sigma(fs,average)<<std::endl;
#if !NO_PLOT  
  plt::show();
#endif
  
  return 0;
}

double run(std::string path, int nreplica)
{
  int imax= 100;//5*nreplica+20;//10*nreplica;
  std::vector<sa::Annealing*> metas;
  std::vector<meta::ASolution * > solutions;
  std::vector<double> Bs;
  //Initialize
  double Mt=0;
  for (int i = 0;i<nreplica;i++)
  {
    sa::Annealing *sa=new sa::Annealing(tsp::randomFromFile(path), 6,50);
    solutions.push_back(sa->oSolution());
    metas.push_back(sa);

    if (Mt<sa->t0())
    {
      Mt=sa->t0();
    }
  }

  Mt*=1.5;
 
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
    }      
    
//    for (int k=0;k<nreplica-1;k++){
      int z = rand()%(nreplica-1);

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
#if !NO_PLOT
  plt::plot(x,y,"o-");
#endif
  double f = min_sol->fitness();
  for (int i = 0;i<solutions.size();i++)
  {
    delete solutions[i];
  }
  return f;
}
