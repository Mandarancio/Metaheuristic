#ifndef META_HPP
#define META_HPP
#include <vector>
#include <string>
namespace meta{
  class ASolution{
  public:
    ASolution(){};
    virtual ~ASolution(){};
    virtual double fitness()=0;
    virtual std::vector<ASolution*> neighbours()=0;
    virtual ASolution * neighbour(int i, int j)=0;
    virtual ASolution * random()=0;
    virtual ASolution * rand_neighbour()=0;
    ASolution * clone()
    {
      return neighbour(0,0);
    };
    virtual int n()=0;
  };
  
  class AMeta{
  public:
    AMeta(ASolution * startSolution, std::string name):
    startSolution_(startSolution), name_(name), iters_(0) {}
    virtual ~AMeta()
    {
      delete startSolution_;
    }
    virtual void reset(ASolution * sol)
    {
      iters_=0;
      delete startSolution_;
      startSolution_= sol;      
    }
    virtual ASolution * step(meta::ASolution * sol)=0;
    virtual ASolution * run()=0;
    virtual int iters(){
      return iters_;
    }
    meta::ASolution * oSolution()
    {
      return startSolution_;
    }
    std::string name()
    {
      return name_;
    }
  protected:
    std::string name_;
    ASolution * startSolution_;
    int iters_;
  };
};

#endif