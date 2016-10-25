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

#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;

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
  plt::plot(fs,"x");
  
  plt::plot({0.,(double)N},{avg,avg},"r--");
  plt::plot({0.,(double)N},{avg+sigma,avg+sigma},"g--");
  plt::plot({0.,(double)N},{avg-sigma,avg-sigma},"g--");
  
  double *ylims = plt::ylim();
  std::vector<double>*hist = hh::histo(fs);
  double alpha = *std::max_element(hist[1].begin(),hist[1].end());
  plt::plot(hist[1],hist[0],"r");
  std::vector<double>x=math::lin_space(ylims[0],ylims[1]);
  std::vector<double>y=math::std_dist(alpha,avg,sigma,x);
  plt::plot(y,x,"r:");
  plt::show();
  return 0;
}
