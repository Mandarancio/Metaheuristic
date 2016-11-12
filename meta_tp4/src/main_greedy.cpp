#include <iostream>
#include "greedy.hpp"
#include "tsp.hpp"
#include "display.hpp"
#include "exmath.hpp"
#include "histo.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;

void plot_tsp_solution(meta::ASolution *s);
void plot_statistics(std::vector<double> fs, double mu, double sigma);
void run(meta::AMeta * meta, std::string path, int N);


int main(int argc, char * argv[])
{
  if (argc!=3)
  {
    std::cout<<"greedy DAT_FILE N_TEST"<<std::endl;
    return -1;
  }
  int N = atoi(argv[2]);

  std::string path(argv[1]);
  srand(time(NULL));
  greedy::Greedy * meta = new greedy::Greedy(NULL);
  run(meta,path,N);
#if !NO_PLOT
  plt::show();
#endif
  return 0;
}


void plot_tsp_solution(meta::ASolution * s)
{
  tsp::Solution * min_sol = dynamic_cast<tsp::Solution*> (s);
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



void plot_statistics(std::vector<double> fs, double mu, double sigma)
{
  plt::figure();
  int N = fs.size();
  plt::plot({0,N-1.},{mu,mu},"r--");
  plt::named_plot("Fitness found",fs,"x-");
  plt::plot({0,N-1.},{mu-sigma,mu-sigma},"g--");
  plt::plot({0,N-1.},{mu+sigma,mu+sigma},"g--");

  if (N>10)
  {
    std::vector<double> * xy=hh::histo(fs,15);
    plt::named_plot("Distribution",xy[1],xy[0],"r-");
    double alpha = *std::max_element(xy[1].begin(),xy[1].end());
    double min_x = *std::min_element(xy[0].begin(),xy[0].end());
    double max_x = *std::max_element(xy[0].begin(),xy[0].end());
    double dx = max_x-min_x;
    min_x-=dx/10.;
    max_x+=dx/10.;
    std::vector<double> x=math::lin_space(min_x,max_x);
    std::vector<double> y = math::std_dist(alpha,mu,sigma,x);
    plt::named_plot("Fit",y,x,"r:");
    double min_y =*std::min_element(fs.begin(),fs.end());
    double max_y =*std::max_element(fs.begin(),fs.end());
  }
  plt::xlabel("t");
  plt::ylabel("fitness");

  plt::legend();

}



void run(meta::AMeta * meta, std::string path, int N)
{
  std::vector<double> best_fit;
  std::vector<double> iters;
  
  double min_fit=10000;
  double t0= 0.0;
  meta::ASolution * min_sol = NULL;
  ok(meta->name());
  display("N Test",N);
  double t=0;
 
  std::cout<<std::endl;
  for (int i = 0;i<N;i++)
  {
    progress(i+1,N);
    tsp::Solution *a= tsp::randomFromFile(path,true);
    meta->reset(a);
    double t1 =  clock();  
    meta::ASolution * best = meta->run();
    t+= (clock()-t1);
    double fitness = best->fitness();
    best_fit.push_back(fitness);
    iters.push_back(meta->iters());
    if (fitness<min_fit)
    {
      delete min_sol;
      min_sol=best;
      min_fit=fitness;
    }else {
      delete best;
    }
    //delete a;
  } 
  std::cout<<std::endl;
  
  double millit = 1000.*(t)/CLOCKS_PER_SEC;

  double avg = math::mean(best_fit);
  double sigma = math::sigma(best_fit,avg);
  double min_it = *std::min_element(iters.begin(),iters.end());
  double max_it = *std::max_element(iters.begin(),iters.end());
  display("Best Fitness",min_fit,"",msg::YELLOW);
  display("Mean Fitness",avg);
  display("Sigma Fitness",sigma);
  display("Total Time",millit,"ms");
  display("Single Run Time",millit/N,"ms");
#if !NO_PLOT
  plot_statistics (best_fit, avg,sigma);
  plot_tsp_solution (min_sol);
#endif
}
