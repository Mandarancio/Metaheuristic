#include "qap.h"
#include <iostream>
#include <time.h>
#include <string>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#if PLOT
#include "matplotlibcpp.hpp"
#include "histo.h"
namespace plt = matplotlibcpp;
#endif 

void display_help(){
  std::cout<<"statistic DAT_FILE N_TEST (options)\n"
  <<" -help show this help\n"
  <<" -i INT number of iteration per Test\n"
  <<" -h show histogram\n"
  <<" -l FLOAT change l coefficent, tabu size is l*n\n"
  <<" -d enable diversification\n";
}

int main(int argc, char* argv[]){
  srand(time(NULL));
  if (argc<3){
    display_help();
    return 0;
  }
  bool histo_on = false;
  bool diversification_on = false;
  std::string path(argv[1]);
  int ntest=atoi(argv[2]);
  double l_coef=1.0;
  int N= 1000;
  for (int i=3;i<argc;i++){
    if (!std::strcmp(argv[i],"-help")){
      display_help();
      return 0;
    }
    else if (!std::strcmp(argv[i],"-h")){
      histo_on=true;
    }
    else if (!std::strcmp(argv[i],"-d")){
      diversification_on=true;
    }else if (!std::strcmp(argv[i],"-l") && i<argc-1){
      l_coef = atof(argv[i+1]);
      i++;
    }else if (!std::strcmp(argv[i],"-i") && i<argc-1){
      N = atoi(argv[i+1]);
      i++;
    }
  }
  
  std::cout<<"\033[1mData file: \033[0m"<<path<<std::endl;
  std::cout<<"\033[1mTests: \033[0m"<<ntest<<std::endl;
  std::cout<<"\033[1mIterations: \033[0m"<<N<<std::endl;
  std::cout<<"\033[1mCoeff. L: \033[0m"<<l_coef<<std::endl;
  std::cout<<"\033[1mDiversification: \033[0m"<<(diversification_on ? "\033[32mtrue\033[0m":"\033[31mfalse\033[0m")<<std::endl;
  QAP::Fitness * f = new QAP::Fitness(path);
  QAP::Metaheuristic meta(f,l_coef,diversification_on);
  
  int n = meta.n();
  int tabu = n*l_coef;
  std::cout<<"\033[1mN: \033[0m"<<n<<std::endl;
  std::cout<<"\033[1mTabu size: \033[0m"<<tabu<<std::endl;
  std::vector<int> results;
  for (int i = 0;i<ntest;i++){
    std::cout<<"\r\033[1mTest: "<<i<<"\033[0m/"<<ntest<<std::flush;
    int best_fitness =-1;
    QAP::Solution * s= new QAP::Solution(f->n());
    s= meta.run(s,N,best_fitness);
    delete s;
    results.push_back(best_fitness);
    
  }
  std::cout<<"\r\033[1mTest: \033[1;32m"<<ntest<<"\033[0m/"<<ntest<<"\n";
  int distance = *std::max_element(results.begin(),results.end());
  int best_fitness = *std::min_element(results.begin(),results.end());
  distance= distance-best_fitness;
  std::cout<<"\033[1mBest fitness: "<<best_fitness<<"\033[0m\n";
  std::cout<<"\033[1mMaximum distance: \033[0m"<<distance<<std::endl;
  #if PLOT
  if (histo_on){
    std::vector<double> * xy = hh::histo(results);
    plt::plot(xy[0],xy[1]);
    plt::show();
  }
  #endif
  return 0;
}
