#include "meta.hpp"
#include <cstdlib>

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
name_(name), startSolution_(startSolution),iters_(0)
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
