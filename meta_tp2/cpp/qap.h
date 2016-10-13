#ifndef QAP_H
#define QAP_H

#include <string>

namespace QAP{

class Solution{
public:
  Solution(int *vec,int n);
  Solution(int n);
  ~Solution();
  Solution * neighbor(int i, int j);
  int n();
  int at(int i);
  int * vec();
  int psi(int i);
private:
  int * vec_;
  int n_;
};


class Fitness{
public:
  Fitness(int n, int* D[], int *W[]);
  Fitness(std::string path);
  ~Fitness();
  int f(Solution * s);
  int delta(Solution * s,int i, int j);
  int n();
private:
  int n_;
  int **D_;
  int **W_;
};

class Metaheuristic{
public:
  Metaheuristic(Fitness *f,double lcoef=1.0);
  Metaheuristic(std::string path,double lcoef=1.0);
  ~Metaheuristic();
  Solution * run(Solution * s, int n_iterations, int & best_fitness);
private:
  Fitness * f_;
  int t_len;
  int n_;
  int **tabu_;
  void init_tabu();
  bool is_tabu(int value,int pos,int t);
  bool set_tabu(int value, int pos, int t);
  int * step(Solution * s, int fitness, int best_fitness,int t);
  
};



};
#endif
