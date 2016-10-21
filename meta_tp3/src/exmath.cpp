#include "exmath.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

double math::gaussian(double alpha, double mu, double sigma, double x)
{
  return alpha*exp(-pow(x-mu,2)/(2*sigma*sigma));
}

std::vector<double> math::std_dist(double alpha, double mu, double sigma, std::vector<double> xs)
{
  std::vector<double> y;
  for (int i =0;i<xs.size();i++){
    y.push_back(math::gaussian(alpha,mu,sigma,xs[i]));
  }
  return y;
}


std::vector<double> math::lin_space(double min, double max, int N)
{
  std::vector<double> x;
  double dx = (max-min)/(N-1);
  for (int i = 0;i<N;i++)
  {
    x.push_back(min+i*dx);
  }
  return x;
}

double math::sigma(std::vector<double> vs, double mu){
  
  double avg = 0;
  for (int i = 0 ;i<vs.size();i++)
  {
    avg+=pow((vs[i]-mu),2);
  }
  return sqrt(avg/vs.size());

}

double math::mean(std::vector<double> vs)
{
  double avg = 0;
  for (int i = 0 ;i<vs.size();i++)
  {
    avg+=vs[i];
  }
  return avg/vs.size();
}

std::vector<double> math::scale(std::vector<double> val, double min, double max)
{
  double ds = max-min;
  double my_min = *std::min_element(val.begin(),val.end());
  double my_max = *std::max_element(val.begin(),val.end());
  double my_ds = my_max-my_min;
  double scale = ds/my_ds;
  if (my_ds ==0 )
  {
    scale = 1.0;
  }
  std::vector<double>s_val;
  for (int i =0;i<val.size();i++)
  {
    s_val.push_back((val[i]-my_min)*scale+min);
  }
  return s_val; 
}
