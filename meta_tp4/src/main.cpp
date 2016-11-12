#include <iostream>
#include "greedy.hpp"
#include "tsp.hpp"
#include "antsystem.hpp"
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

void save_csv(std::string path, int ants_n, int iter_n, double exec_t, double best_fit, double mean_fit, double sigma_fit, int test_n);

void help();

int main(int argc, char * argv[])
{
  if (argc<2)
  {
    alert("Wrong synthax");
    help();
    return 0;
  }
  ok("Ant System Meta");
  srand(time(NULL));
  std::string path(argv[1]);
  int N = 20;
  int n_ants =-1;
  int iters = 25;
  bool do_plot = true;
  bool csv = false;
  std::string csv_path;
  for (int i =1;i<argc;i++)
  {
    if (!strcmp(argv[i],"-h"))
    {
      help();
      return 0;
    }
    else if (!strcmp(argv[i],"-n") && i+1<argc)
    {
      i++;
      N=atoi(argv[i]);
    }
    else if (!strcmp(argv[i],"-ants") && i+1<argc)
    {
      i++;
      n_ants=atoi(argv[i]);
    }
    else if (!strcmp(argv[i],"-iter") && i+1<argc)
    {
      i++;
      iters= atoi(argv[i]);
    }
    else if (!strcmp(argv[i],"-csv") && i+1<argc)
    {
      i++;
      csv=true;
      csv_path = std::string(argv[i]);
    }
    else if (!strcmp(argv[i],"-no_plot"))
    {
      do_plot = false;
    }
  }

  //load the generetor solution 
  tsp::Solution * ss =tsp::fromFile(path);
  //initalize a greedy meta
  greedy::Greedy * g_meta = new greedy::Greedy(tsp::randomFromFile(path));
  //compute Lnn value using a greedy meta
  double lnn = g_meta->run()->fitness();
  //create the ant group knowledge
  as::GroupKnowledge * gk = new as::GroupKnowledge(ss,1./lnn,1,5,lnn,0.1);
  //check if ants number was user defined
  if (n_ants<=0)
  {
    n_ants=gk->n()>50 ? 50:gk->n(); // n ants
  }
  
  
  //load a random solution
  meta::ASolution * ts  = tsp::randomFromFile(path);
  //initialize the ant system
  as::AntSystem * antSystem = new as::AntSystem(ts,gk,n_ants,iters);
  
  //statistic variables
  std::vector<double>fs;
  double best = ts->fitness();
  meta::ASolution *best_s=ts->clone();
  double total_t = 0;
  
  display("N Test",N);
  display("N Ants",n_ants);
  display("N Iters",iters);
  display("Problem Size",gk->n());
  std::cout<<std::endl;
  //start the run
  for (int i = 0;i<N;i++){
    progress(i+1,N);
    double t=clock();
    antSystem->reset(tsp::randomFromFile(path));
    meta::ASolution * s = antSystem->run();
    t = clock() - t;
    total_t += 1000.*t/CLOCKS_PER_SEC;
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
  std::cout<<std::endl;
  //compute and display the result
  double mean_f= math::mean(fs);
  double sigma_f = math::sigma(fs,mean_f);
  display("Best Fitness",best,"",msg::YELLOW);
  display("Mean Fitness",mean_f);
  display("Sigma Fitness", sigma_f);
  display("Total Time",total_t,"ms");
  display("Single Run Time",total_t/N,"ms");
  
  if (csv) 
  {
    save_csv(csv_path,n_ants,iters,total_t/N,best,mean_f,sigma_f,N);
  }
  if (do_plot)
  {
    plot_tsp_solution(best_s);
    plot_statistics(fs,mean_f,sigma_f);
    plt::show();
  }
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
  <<" -n INT    : number of test to run (default: 10)"<<std::endl
  <<" -h        : show the help"<<std::endl
  <<" -ants INT : set number of ants (default: N_CITIES || 50 )"<<std::endl
  <<" -iter INT : set number of iterations for run (default: 25)"<<std::endl
  <<" -csv PATH : save statistics to csv file"<<std::endl
  <<" -no_plot  : no plot output"<<std::endl;
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

void save_csv(std::string path, int ants_n, int iter_n, double exec_t, double best_fit, double mean_fit, double sigma_fit, int test_n)
{
  bool write_labels = false;
  {
    std::ifstream f(path.c_str());
    write_labels=!f.good();
  }
  std::ofstream of;
  of.open(path.c_str(), std::ofstream::out | std::ofstream::app);
  if (write_labels)
  {
    of<<"N Ants,N Iters,Exec T,Best f,Mean f,Sigma f,N Test"<<std::endl;
  }
  of<<ants_n<<","<<iter_n<<","<<exec_t<<","<<best_fit<<","<<mean_fit<<","<<sigma_fit<<","<<test_n<<std::endl;
  of.close();
}
