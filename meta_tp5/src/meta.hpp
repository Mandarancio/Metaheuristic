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
    virtual double sub_fitness(int i,int j)=0;
    virtual ASolution * create(std::vector<int> is)=0;
    ASolution * clone();
    virtual int n()=0;
    virtual std::string to_string()=0;
  };
  
  class RnSolution: public ASolution
  {
  public:
    RnSolution(std::vector<double> sol, std::vector<double> mins, std::vector<double> maxs, double (*f)(std::vector<double>));
    RnSolution(int n, std::vector<double> mins, std::vector<double> maxs, double (*f)(std::vector<double>));
    ~RnSolution();
    double max(int d);
    double min(int d);
    std::vector<double> max();
    std::vector<double> min();
    std::vector<double> solution();
    virtual ASolution * neighbour(int i, int j);
    virtual ASolution * random();
    virtual ASolution * rand_neighbour();
    virtual ASolution * sub_solution(int i, int j);
    virtual double sub_fitness(int i,int j);
    virtual double fitness();
    virtual std::vector<ASolution*> neighbours();
    virtual int n();
    virtual std::string to_string();
    virtual ASolution * create(std::vector<int> is);
    RnSolution * create(std::vector<double> x);
  private:
    int n_;
    std::vector<double> min_;
    std::vector<double> max_;
    std::vector<double> solution_;
    double (*fitness_function_)(std::vector<double>);
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
