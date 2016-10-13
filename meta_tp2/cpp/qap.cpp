#include "qap.h"
#include <string.h>
#include <fstream>
#include <cmath>
#include <climits>
#include <cstdlib>

using namespace QAP;


int * intdup(int const * src, size_t len)
{
  int * p = new int[len];
  memcpy(p, src, len * sizeof(int));
  return p;
}

Solution::Solution(int * vec, int n){
  this->vec_=intdup(vec,n);
  this->n_ =n;
}

Solution::Solution(int n){
  this->vec_=new int[n];
  this->n_ = n;
  for (int i=0;i<n;i++){
    this->vec_[i] = i+1;
  }
  for (int i=0;i<10*n;i++){
    int x = rand()%n;
    int y = rand()%n;
    while (x==y){
      y= rand()%n;
    }
    int a = vec_[x];
    vec_[x]=vec_[y];
    vec_[y]=a;
  }
}

Solution::~Solution(){
  if (vec_!=NULL){
    delete this->vec_;
  }
}

int Solution::at(int i){
  if (i<0 || i>=this->n_){
    return -1;
  }
  return this->vec_[i];
}

Solution * Solution::neighbor(int i, int j){
  int * v = intdup(this->vec_,this->n_);
  v[i]=this->vec_[j];
  v[j]=this->vec_[i];
  Solution * s = new Solution(v,this->n_);
  delete v;
  return s;
}

int Solution::n(){
  return this->n_;
}

int * Solution::vec(){
  return this->vec_;
}

int Solution::psi(int j){
  for (int i = 0; i < this->n_; i++){
    if (this->vec_[i]==j){
      return i;
    }
  }
  return 0;
}


Fitness::Fitness(int n, int* D[], int *W[]){
  this->n_=n;
  this->W_= W;
  this->D_= D;
}

Fitness::Fitness(std::string path){
  std::ifstream infile(path);
  int n;
  infile>>n;
  this->n_=n;

  this->D_=new int*[n];
  for (int i=0;i<n;i++){
    this->D_[i]=new int[n];
    for (int j=0; j<n;j++){
      int v;
      infile>>v;
      this->D_[i][j]=v;
    }
  }
  this->W_=new int*[n];
  for (int i=0;i<n;i++){
    this->W_[i]=new int[n];
    for (int j=0; j<n;j++){
      int v;
      infile>>v;
      this->W_[i][j]=v;
    }
  }
  infile.close();

}

Fitness::~Fitness(){
  delete[] this->D_;
  delete[] this->W_;
}

int Fitness::f(Solution * s){
  int I = 0;
  int l = s->n();
  for (int i =0; i<l-1;i++){
    int di = s->psi(i+1);
    for (int j=i+1;j<l;j++){
      int w = this->W_[i][j];
      int dj = s->psi(j+1);
      int d = this->D_[di][dj];
      I += w * d;
    }
  }
  return 2*I;
}

int Fitness::delta(Solution * s,int i, int j){
  int delta = 0;
  int si = s->at(i)-1;
  int sj = s->at(j)-1;
  for (int k=0; k < s->n(); k++){
      if (k == si or k == sj){
          continue;
      }
      int dk = s->psi(k+1);
      int dd = (this->W_[k][si]-this->W_[k][sj])*(this->D_[dk][i]-this->D_[dk][j]);
      delta += dd;
  }
  return 2*delta;
}

int Fitness::n(){
  return this->n_;
}

Metaheuristic::Metaheuristic(Fitness *f,double lcoef,bool diversification){
  this->f_=f;
  this->diversification_=diversification;
  this->n_=f->n();
  this->div_len=n_*n_;
  init_tabu();
  this->t_len=round(lcoef*n_);
}

Metaheuristic::Metaheuristic(std::string path,double lcoef,bool diversification){
  this->diversification_=diversification;
  this->f_ = new Fitness(path);
  this->n_ = this->f_->n();
  this->div_len=n_*n_;
  this->t_len=round(lcoef*n_);
  init_tabu();
}

Metaheuristic::~Metaheuristic(){
  if (this->f_)
    delete this->f_;
  if (this->tabu_)
    delete[] this->tabu_;
}

void Metaheuristic::init_tabu(){
  this->tabu_= new int*[n_];
  for (int i=0;i<n_;i++){
    tabu_[i]=new int[n_];
    for (int j =0; j<n_;j++){
      tabu_[i][j]=0;
    }
  }
}


bool Metaheuristic::is_tabu(int value,int pos, int t){
  return tabu_[value-1][pos]>t;
}

bool Metaheuristic::is_mandatory(int value,int pos,int t){
  return diversification_ &&  tabu_[value-1][pos]<t-div_len;
}

bool Metaheuristic::set_tabu(int value, int pos, int t){
  tabu_[value-1][pos]=t+t_len;
}

int * Metaheuristic::step(Solution * s, int fitness, int best_fitness, int t){
  int * res = new int[3];
  res[0] =  INT_MAX; //fitness
  res[1] = -1; // perm i
  res[2] = -1; // perm j
  for (int i = 0;i < s->n()-1;i++){
    for (int j = i+1;j<s->n();j++){
      int f = fitness - f_->delta(s,i,j);
      if (f<res[0] && f<best_fitness){
        res[0]=f;
        res[1]=i;
        res[2]=j;
      }else if (res[0]>=best_fitness){
        if (is_mandatory(s->at(i),j,t) && is_mandatory(s->at(i),j,t)){
          res[0]=f;
          res[1]=i;
          res[2]=j;
          return res;
        }
        else if (!is_tabu(s->at(i),j,t) && !is_tabu(s->at(j),i,t)){
          if (f<res[0]){
            res[0]=f;
            res[1]=i;
            res[2]=j;
          }
        }
      }
    }
  }
  return res;
}

Solution * Metaheuristic::run(Solution * s, int n_iterations, int & best_fitness){
  Solution * best = s;
  best_fitness = f_->f(s);
  history_f_.clear();
  history_t_.clear();
  avg_=0;
  all_history_f_.clear();
  int fitness = best_fitness;
  for (int i = 0; i < n_iterations;i++){
    int * res = this->step(s,fitness,best_fitness,i);
    if (res[1]>=0){
      avg_+=res[0];
      all_history_f_.push_back(res[0]);
      Solution * snext = s->neighbor(res[1],res[2]);
      set_tabu(s->at(res[1]),res[1],i);
      set_tabu(s->at(res[2]),res[2],i);
      if (best != s){
        delete s;
      }
      if (res[0]<best_fitness){
        best_fitness=res[0];
        history_f_.push_back(best_fitness);
        history_t_.push_back(i);
        delete best;
        best = snext;
      }     
      s = snext;
      fitness = res[0];
    }else{
      all_history_f_.push_back(fitness);
      avg_+=fitness;
    }
    delete res;
  }
  return best;
}

std::vector<int> Metaheuristic::history_t(){
  return this->history_t_;
}

std::vector<int> Metaheuristic::history_f(){
  return this->history_f_;
}
std::vector<int> Metaheuristic::all_history_f(){
  return this->all_history_f_;
}

double Metaheuristic::average(){
  if (all_history_f_.size()==0)
    return -1;
  return avg_/(double)all_history_f_.size();
  
}

int Metaheuristic::n(){
  return this->n_;
}
