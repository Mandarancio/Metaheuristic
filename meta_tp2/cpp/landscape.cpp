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
  std::cout<<"landscape DAT_FILE (options)\n"
  <<" -help show this help\n"
  <<" -s INT size of the landscape\n"
  <<" -h show histogram\n"
  <<" -hg show histogram and gauss fit\n"
  <<" -p show plot\n"
  <<" -pg show plot distribution\n";
}

double gaussian(double x, double a, double b, double c){
  return a*exp(-(pow(x-b,2)/(2*c*c)));
}

int main(int argc, char * argv[])
{
  if ( argc < 2 )
  {
    display_help();
    return 0;
  }
  int n = 1000;
  bool plot_on = false;
  bool histo_on = false;
  bool gauss_on = false;
  bool plot_gauss_on =false;
  std::string path(argv[1]);
  for (int i = 2;i<argc;i++)
  {
    if (!std::strcmp(argv[i],"-help"))
    {
      display_help();
      return 0;
    } else if (!std::strcmp(argv[i],"-h"))
    {
      histo_on = true;
    }else if (!std::strcmp(argv[i],"-p"))
    {
      plot_on = true;
    }else if (!std::strcmp(argv[i],"-s") && i<argc-1)
    {
      n = atoi(argv[i+1]);
      i++;    
    }else if (!std::strcmp(argv[i],"-hg"))
    {
      histo_on = true;
      gauss_on = true;
    }else if (!std::strcmp(argv[i],"-pg"))
    {
      plot_on=true;
      plot_gauss_on=true;
    }
  }
  QAP::Fitness f(path);
  long avg_fitness = 0;
  std::vector<int> landscape;
  std::vector<int> solutions_hash;
  std::cout<<"\033[1mData file: \033[0m"<<path<<std::endl;
  std::cout<<"\033[1mN: \033[0m"<<f.n()<<std::endl;
  std::cout<<"\033[1mLandscape size: \033[0m"<<n<<std::endl;
  
  for (int i=0;i<n;i++){
    std::cout<<"\r\033[1mComputed: "<<(i+1)<<"\033[0m/"<<n<<std::flush;
    QAP::Solution s(f.n());
    solutions_hash.push_back(i);
    int fitness = f.f(&s);
    landscape.push_back(fitness);
    avg_fitness+=fitness;   
  }  
  
  std::cout<<"\r\033[1mComputed: "<<n<<"\033[0m/"<<n<<std::endl;
  double average = (double)avg_fitness/n;
  double dist_avg =0.;
  for (int i =0;i<n;i++)
  {
    dist_avg+=abs(landscape[i]-average);
  }
  dist_avg/=(double)n;
  std::cout<<"\033[1mAverage fitness: \033[0m"<<average<<std::endl;
  int max = *std::max_element(landscape.begin(),landscape.end());
  int min = *std::min_element(landscape.begin(),landscape.end());
  std::cout<<"\033[1mMax fitness: \033[0m"<<max<<std::endl;
  std::cout<<"\033[1mMin fitness: \033[0m"<<min<<std::endl;
  std::cout<<"\033[1mAvg distance:\033[0m"<<dist_avg<<std::endl;
#if PLOT
  if (plot_on){
    int l = landscape.size();
    plt::named_plot("landscape",solutions_hash,landscape,"black");
    plt::named_plot("average",{0.,(double)l},{average,average},"r--");
    plt::plot({0.,(double)l},{average-dist_avg,average-dist_avg},"w--");
    plt::plot({0.,(double)l},{average+dist_avg,average+dist_avg},"w--"); 
    
    if (plot_gauss_on)
    {
      double max_x =(double) max; 
      double min_x =(double)min;
      double dx=(max_x-min_x)/100.0;
      std::vector<double> x;
      std::vector<double> y;
      std::vector<double> *xy = hh::histo(landscape,20);
      double max_y = *std::max_element(xy[1].begin(),xy[1].end());
      for (int i=0;i<100;i++)
      {
        double xt = min_x+i*dx;
        double yt = gaussian(xt,max_y,average,dist_avg);
        x.push_back(xt);
        y.push_back(yt);
      }
      plt::named_plot("histogram",xy[1],xy[0]);
      plt::named_plot("distribution curve",y,x);

    }
    plt::legend();
    plt::xlabel("time");
    plt::ylabel("fitness");
  }
  if (plot_on && histo_on)
  {
    plt::figure();
  }
  if (histo_on)
  {
    std::vector<double> *xy = hh::histo(landscape,10,false);
    double max_y = *std::max_element(xy[1].begin(),xy[1].end());
    plt::named_plot("fitness histogram",xy[0],xy[1],"black");
    plt::named_plot("average",{average,average},{0.,max_y*1.01},"g--");
    plt::plot({average-dist_avg,average-dist_avg},{0,max_y*1.01},"r--");
    plt::plot({average+dist_avg,average+dist_avg},{0,max_y*1.01},"r--");
    if (gauss_on)
    {
      std::vector<double> x;
      std::vector<double> y;
      double max_x = xy[0][xy[0].size()-1];
      double min_x = xy[0][0];
      double dx=(max_x-min_x)/100.0;
      for (int i=0;i<100;i++){
        double xt = min_x+i*dx;
        double yt = gaussian(xt,max_y,average,dist_avg);
        x.push_back(xt);
        y.push_back(yt);
      }
      plt::named_plot("fit curve",x,y);
    }
    plt::ylim(0.,max_y*1.01);
    plt::xlabel("fitness");
    plt::ylabel("occurency");
    plt::legend();
  }
  if (histo_on || plot_on)
  {
    plt::show();
  }
#endif
}
