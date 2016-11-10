#include <iostream>
#include "greedy.hpp"
#include "tsp.hpp"
#include "antsystem.hpp"
#include "display.hpp"
#include "exmath.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;

void plot_tsp_solution(meta::ASolution *s);
void help();

int main(int argc, char * argv[])
{
  if (argc!=2){
    alert("Please use the commands");
    return 0;
  }
  ok("Ant System Meta");
  srand(time(NULL));
  std::string path(argv[1]);
  tsp::Solution * ss =tsp::fromFile(path); 
  greedy::Greedy * g_meta = new greedy::Greedy(tsp::randomFromFile(path));
  double lnn = g_meta->run()->fitness();
  as::GroupKnowledge * gk = new as::GroupKnowledge(ss,1./lnn,1,5,lnn,0.1);
  meta::ASolution * ts  = tsp::randomFromFile(path);
  int ntot = gk->n()>25? 25:gk->n();
  as::AntSystem * antSystem = new as::AntSystem(ts,gk,ntot,15);
  std::vector<double>fs;
  double best = ts->fitness();
  meta::ASolution *best_s=ts->clone();
  int total_t = 0;
  int N=20;
  
  for (int i = 0;i<N;i++){
    progress(i+1,N);
    int t=clock();
    meta::ASolution * s = antSystem->run();
    t = clock() - t;
    total_t += round(1000.*((double)t)/CLOCKS_PER_SEC);
    double f =s->fitness();
    fs.push_back(f);
    if (s->fitness()<best)
    {
      best = f;
      delete best_s;
      best_s =s;
    }else{
      delete s;
    }
  }
  double mean_f= math::mean(fs);
  double sigma_f = math::sigma(fs,mean_f);
  display("Best Fitness",best,"",msg::YELLOW);
  display("Mean Fitness",mean_f);
  display("Sigma Fitness", sigma_f);
  display("Total Time",total_t,"ms");
  display("Single Run TIme",total_t/N,"ms");
  plot_tsp_solution(best_s);
  plt::show();
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

void help()
{
  std::cout
  <<"analyse FILE_DATA [options]"<<std::endl
  <<" -n INT : number of test to run"<<std::endl
  <<" -h : show the help"<<std::endl;
}
