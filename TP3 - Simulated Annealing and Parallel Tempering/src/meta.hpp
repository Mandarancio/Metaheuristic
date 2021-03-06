#ifndef META_HPP
#define META_HPP
#include <vector>
#include <string>
namespace meta{
  class ASolution{
  public:
    ASolution();
    virtual ~ASolution();
    virtual double fitness()=0;
    virtual double delta_fitness(int i, int j);
    virtual std::vector<ASolution*> neighbours()=0;
    virtual ASolution * neighbour(int i, int j)=0;
    virtual ASolution * random()=0;
    virtual ASolution * rand_neighbour()=0;
    virtual ASolution * sub_solution(int i, int j)=0;
    ASolution * clone();
    virtual int n()=0;
  };
  
  class AMeta{
  public:
    AMeta(ASolution * startSolution, std::string name);
    virtual ~AMeta();
    virtual void reset(ASolution * sol);
    virtual ASolution * step(meta::ASolution * sol)=0;
    virtual ASolution * run()=0;
    virtual int iters();
    meta::ASolution * oSolution();
    std::string name();
  protected:
    std::string name_;
    ASolution * startSolution_;
    int iters_;
  };
  
  std::vector <ASolution *> sol_landscape(ASolution * s, int N);
  std::vector <double> landscape(ASolution * s, int  N);
};

#endif
