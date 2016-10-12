#include "qap.h"
#include <string.h>

int * intdup(int const * src, size_t len)
{
   int * p = new int[len];
   memcpy(p, src, len * sizeof(int));
   return p;
}

Solution::Solution(int * vec, int n){
  this->vec_=vec;
  this->n_ =n;
}
Solution::~Solution(){
  delete this->vec_;
}

Solution * Solution::neighbor(int i, int j){
  int * v = intdup(this->vec_,this->n_);
  v[i]=this->vec_[j];
  v[j]=this->vec_[i];
  return new Solution(v,this->n_);
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
      return i+1;
    }
  }
  return 0;
}
