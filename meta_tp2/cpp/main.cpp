#include "qap.h"
#include <iostream>
#include <time.h>
#include <string>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#if PLOT
#include "matplotlibcpp.hpp"
#include <vector>
#include "histo.h"
#include <algorithm>
namespace plt = matplotlibcpp;
#endif 
using namespace std;


void print(QAP::Solution * s){
  int n = s->n();
  int * vec = s->vec();
  std::cout<<"[ "<<vec[0];
  for (int i = 1; i < n; i++){
    std::cout<<", "<<vec[i];
  }
  std::cout<<" ]\n";
}


int main(int argc, char const *argv[]) {
  std::string path = "1.dat";
  float l = 1.0; 
  bool diversification =false;
  int N = 1000;
  bool plot=false;
  bool histo = false;
  int bins = 20;
  for (int i = 1;i<argc;i++){
    if (strcmp(argv[i],"-f")==0 && i+1<argc){
      path = std::string(argv[i+1]);
      i++;
    }else if (strcmp(argv[i],"-l")==0 && i+1<argc){
      l=atof(argv[i+1]);
      i++;
    }else if (strcmp(argv[i],"-n")==0 && i+1<argc){
      N=atoi(argv[i+1]);
      i++;
    }else if (strcmp(argv[i],"-p")==0){
      plot=true;
    }else if (strcmp(argv[i],"-h")==0){
      histo=true;
    }else if (strcmp(argv[i],"-b")==0 && i+1<argc){
      bins=atoi(argv[i+1]);
      i++;
    }else if (strcmp(argv[i],"-d")==0){
      diversification=true;
    }
  }
  
  srand(time(NULL));
  QAP::Fitness *f = new QAP::Fitness(path);
  QAP::Solution * s= new QAP::Solution(f->n());
  cout<<"\033[1mStarting S\033[0m: ";
  print(s);
  cout<<"\033[1mStart fitness\033[0m: "<<f->f(s)<<endl;
  cout<<"\033[1mIterations\033[0m: "<<N<<endl;
  cout<<"\033[1mL Coef\033[0m: "<<l<<endl;
  cout<<"\033[1mProcessing... \033[0m"<<flush;
  int bf=-1;
  QAP::Metaheuristic m(f,l,diversification);
  clock_t t;
  t=clock();
  QAP::Solution * best = m.run(s,N,bf);
  t = clock() - t;
  int millit = round(1000.*((double)t)/CLOCKS_PER_SEC);
  cout<<"\r\033[1mProcessing: \033[0m\033[1;32mDONE\033[0m\n";
  cout<<"\033[1mBest S\033[0m: ";
  print(best);
  cout<<"\033[1mBest fitness\033[0m: "<<bf<<endl;
  int rf = f->f(best);
  cout<<"\033[1mRe-Computed fitness\033[0m: "<<rf<<endl;
  
  cout<<"\033[1mAverage fitness\033[0m: "<<m.average()<<endl;
  cout<<"\033[1mTest\033[0m: "<< (rf==bf ?"\033[1;32mTrue\033[0m\n": "\033[1;31mFalse\033[0m\n");
  cout<<"\033[1mTime\033[0m: "<<millit<<" ms"<<endl;
  cout<<"\033[1mTime per iteration\033[0m: "<<(double)millit/N<<" ms"<<endl;
#if PLOT
  if (plot){
    double x_max = (double)m.all_history_f().size();
    plt::plot(m.history_t(),m.history_f(),"ro-");
    plt::plot(m.all_history_f(),"-");
    plt::plot({0,x_max},{(double)bf,(double)bf},"--");
    plt::plot({0,x_max},{m.average(),m.average()},"k--");
  }
  if (histo && plot){
    plt::figure();
  }
  if (histo){
    std::vector<int> xs = m.all_history_f();
    std::vector<double> * xy=hh::histo(xs,bins,true);
    double max = *std::max_element(xy[1].begin(),xy[1].end());
    max+=0.1*max;
    plt::plot(xy[0],xy[1]);
    plt::plot({m.average(),m.average()},{0,max},"--");
    plt::ylim(0.,max);
  }
  if (histo || plot){
    plt::show();
  }
#endif
  return 0;
}
