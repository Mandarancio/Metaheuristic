#ifndef QAP_H
#define QAP_H

#include <string>
#include <vector>

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
  Metaheuristic(Fitness *f,double lcoef=1.0,bool diversification=false);
  Metaheuristic(std::string path,double lcoef=1.0, bool diversification=false);
  ~Metaheuristic();
  Solution * run(Solution * s, int n_iterations, int & best_fitness);
  std::vector<int> history_f();
  std::vector<int> history_t();
  std::vector<int> all_history_f();
  double average();
  int n();

private:
  Fitness * f_;
  bool diversification_;
  int t_len;
  int div_len;
  int n_;
  long avg_;
  int **tabu_;
  std::vector<int> history_f_;
  std::vector<int> history_t_;
  std::vector<int> all_history_f_;
 
  void init_tabu();
  bool is_tabu(int value,int pos,int t);
  bool is_mandatory(int value, int pos, int t);
  bool set_tabu(int value, int pos, int t);
  int * step(Solution * s, int fitness, int best_fitness,int t);
};



};
#endif
