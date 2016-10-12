#ifndef QAP_H
#define QAP_H

class Solution{
public:
  Solution(int *vec,int n);
  ~Solution();
  Solution * neighbor(int i, int j);
  int n();
  int * vec();
  int psi(int i);
private:
  int * vec_;
  int n_;
};

class Fitness{

};

#endif
