#ifndef QAP_H
#define QAP_H

#include <string>
#include <vector>

namespace QAP{

  class Solution{
  public:
    Solution(int *vec,int n); //create a solution from a defined array of facilities of size N
    Solution(int n); //create a random solution of size N
    ~Solution();
    Solution * neighbor(int i, int j); //get a neighbor switching the facility in i with the one in  j
    int n(); //size of the solution
    int at(int i); //Facility at position i 
    int * vec(); //array of facilities
    int psi(int i); //location of a facility i

  private:
    int * vec_;
    int n_;
  };


  class Fitness{
  public:
    Fitness(int n, int* D[], int *W[]); //load 
    Fitness(std::string path); //load the matrix directly from file
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
