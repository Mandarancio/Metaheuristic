#include "tsp.hpp"
#include "meta.hpp"
#include "exmath.hpp"
#include "histo.hpp"

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#if !NO_PLOT
#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;
#endif
int main(int argc, char *argv[])
{
  if (argc!=3)
  {
    std::cout<<"landscape FILE_DAT N_SOL"<<std::endl;
    return -1;  
  }
  srand(time(NULL));
  int N=std::atoi(argv[2]);
  std::string path(argv[1]);
  meta::ASolution * s = tsp::randomFromFile(path);
  std::vector<double> fs = meta::landscape(s,N);
  delete s;
  double avg =math::mean(fs);
  double sigma = math::sigma(fs,avg);
  std::cout<<"\033[1mMean: \033[0m"<<avg<<std::endl;
  std::cout<<"\033[1mStd. Deviation: \033[0m"<<sigma<<std::endl;
#if !NO_PLOT
  plt::named_plot("landscape",fs,"x");
  
  plt::named_plot("average",{0.,(double)N},{avg,avg},"r--");
  plt::named_plot("std deviations",{0.,(double)N},{avg+sigma,avg+sigma},"g--");
  plt::plot({0.,(double)N},{avg-sigma,avg-sigma},"g--");
  
  double *ylims = plt::ylim();
  std::vector<double>*hist = hh::histo(fs,15);
  double alpha = *std::max_element(hist[1].begin(),hist[1].end())*1.1;
  std::cout<<"\033[1mAlpha: \033[0m"<<alpha<<std::endl;
  plt::named_plot("fitness distribution",hist[1],hist[0],"r");
  std::vector<double>x=math::lin_space(ylims[0],ylims[1]);
  std::vector<double>y=math::std_dist(alpha,avg,sigma,x);
  plt::named_plot("gaussian fit",y,x,"k--");
  plt::xlabel("t");
  plt::ylabel("fitness");
  plt::title("TSP Landscape");
  plt::legend();
  plt::show();
#endif
  return 0;
}
