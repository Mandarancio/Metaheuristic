#ifndef META_HPP
#define META_HPP
#include <vector>
#include <ostream>
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
    virtual int n()=0;
  };
};

#endif
