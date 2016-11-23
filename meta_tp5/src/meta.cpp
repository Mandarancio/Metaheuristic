#include "meta.hpp"
#include <cstdlib>
#include <sstream>

using namespace meta;

ASolution::ASolution()
{}

ASolution::~ASolution()
{}

double ASolution::delta_fitness(int i, int j)
{
      ASolution * n = neighbour(i,j);
      double de = n->fitness()-fitness();
      delete n;
      return de;
}

ASolution * ASolution::clone()
{
      return neighbour(0,0);
}

AMeta::AMeta(ASolution * startSolution, std::string name):
startSolution_(startSolution), name_(name), iters_(0) 
{}

AMeta::~AMeta()
{
      delete startSolution_;
}

void AMeta::reset(ASolution * sol)
{
      iters_=0;
      delete startSolution_;
      startSolution_= sol;      
}

int AMeta::iters()
{
      return iters_;
}

meta::ASolution * AMeta::oSolution()
{
      return startSolution_;
}

std::string AMeta::name()
{
      return name_;
}

std::vector <double> meta::landscape(ASolution * s, int  N)
{
    std::vector<double> res;
    for (int i=0;i<N;i++){
        ASolution * x = s->random();
        res.push_back(x->fitness());
        delete x;
    }
    return res;
}
  
std::vector <ASolution *> meta::sol_landscape(ASolution * s, int N)
{
    std::vector<ASolution*> res;
    for (int i=0;i<N;i++){
        res.push_back(s->random());
    }
    return res;
}


RnSolution::RnSolution(std::vector<double> sol, std::vector<double> mins, std::vector<double> maxs,double (*f)(std::vector<double>)):
solution_(sol), max_(maxs), min_(mins), fitness_function_(f)
{
  n_ = sol.size();
}
RnSolution::RnSolution(int n, std::vector<double> mins, std::vector<double> maxs, double (*f)(std::vector<double>)):
n_(n),max_(maxs),min_(mins),fitness_function_(f)
{
  for (int i = 0 ;i<n;i++)
  {
    double x = double(rand())/RAND_MAX*(max_[i]-min_[i])+min_[i]; 
    solution_.push_back(x);
  }
}

RnSolution::~RnSolution()
{
  solution_.clear();
  min_.clear();
  max_.clear();
}

double RnSolution::max(int d)
{
  return max_[d];
}


double RnSolution::min(int d)
{
  return min_[d];
}

std::vector<double> RnSolution::max()
{
  return max_;
}
    
std::vector<double> RnSolution::min()
{
  return min_;
}

std::vector<double> RnSolution::solution()
{
  return solution_; 
}

ASolution * RnSolution::neighbour(int i, int j)
{
  std::vector<double> clone(solution_);
  clone[i]=solution_[j];
  clone[j]=solution_[i];
  return new RnSolution(clone,min_,max_,fitness_function_);
}

ASolution * RnSolution::random()
{
  std::vector<double> r;
  for (int i=0;i<n_;i++)
  {
    double x = double(rand())/RAND_MAX*(max_[i]-min_[i])+min_[i]; 
    r.push_back(x);
  }
  return new RnSolution(r,min_,max_,fitness_function_);
}

ASolution * RnSolution::rand_neighbour()
{
  return random();
}

ASolution * RnSolution::sub_solution(int i, int j){
  return NULL;
}

std::vector<ASolution*> RnSolution::neighbours()
{
  std::vector<ASolution*> r;
  for (int i =0;i<n_;i++)
  {
    r.push_back(random());
  }
  return r;
}

ASolution * RnSolution::create(std::vector<int> is)
{
  std::vector<double> x;
  for (int i = 0;i<n_;i++)
  {
    x.push_back(solution_[is[i]]);
  }
  return new RnSolution(x,min_,max_,fitness_function_);
}

double RnSolution::sub_fitness(int i,int j)
{
 return 0; 
}
double RnSolution::fitness()
{
  return fitness_function_(solution_);
}

int RnSolution::n()
{
  return n_;
}

RnSolution * RnSolution::create(std::vector<double> x)
{
  return new RnSolution(x,min_,max_,fitness_function_);
}

std::string RnSolution::to_string()
{
  std::stringstream bff;
  bff<<"["<<solution_[0];
  for (int i=1;i<n_;i++)
  {
    bff<<", "<<solution_[i];
  }
  bff<<"] : "<<fitness();
  return bff.str();
}
