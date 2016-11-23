#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "exmath.hpp"
#include "meta.hpp"
#include "pso.hpp"

#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;



double f(std::vector<double> x)
{
  return math::sinc(x[0])*math::sinc(x[1]);
}

void plot(std::vector<double> xs, std::vector<double>ys, std::vector<std::vector<double> > zs,std::vector<pso::Particle*> ps,int id)
{
  plt::figure();
  plt::contour(xs,ys,zs);

  for (unsigned int i =0;i<ps.size();i++)
  {
    double x=ps[i]->current_position()->solution()[0];
    double y=ps[i]->current_position()->solution()[1];
    double sx= ps[i]->speed()[0];
    double sy= ps[i]->speed()[1];
    plt::plot({x},{y},"o");
    plt::arrow(x,y,sx,sy);
  }
  plt::save("plots/step"+std::to_string(id)+".png");
  plt::close();
}

int main(int argc, char *argv[])
{
  int n = 2;
  double min[2]={-9,-9};
  double max[2]={9,9};
  srand(time(NULL));
  meta::RnSolution *r;
  r = new meta::RnSolution(n,std::vector<double>(min,min+2),std::vector<double>(max,max+2),f);
  std::cout<<r->to_string()<<std::endl;
  pso::PSO * meta= new pso::PSO(r,10,30,0.5,0.1,0.3,3.);
  std::vector<double>xs,ys;
  std::vector<std::vector<double> >zs;

  for (double x=-9;x<=9;x+=0.05){
    xs.push_back(x);
    ys.push_back(x);
  }
  for (unsigned int i =0; i<xs.size();i++)
  {
    zs.push_back(std::vector<double>());
    double x = xs[i];
    for (unsigned int j = 0; j<ys.size();j++)
    {
      double y = ys[j];
      double z = math::sinc(x)*math::sinc(y);
      zs[i].push_back(z);
    }
  }

  meta::ASolution * best = r->clone();

  for (int i =0;i<10;i++)
  {
    std::vector<pso::Particle *> ps=meta->particles();

    plot(xs,ys,zs,ps,i);
    meta::ASolution * next = meta->step(best);
    if (next!=best)
    {
      delete best;
      best = next;
    }
  }

  std::vector<pso::Particle *> ps=meta->particles();

  plot(xs,ys,zs,ps,10);

  std::cout<<best->to_string()<<std::endl;

  plt::show();
}
