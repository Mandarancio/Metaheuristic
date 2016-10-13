#include "qap.h"
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;


void print(QAP::Solution * s){
  int n = s->n();
  int * vec = s->vec();
  std::cout<<"[ "<<vec[0];
  for (int i = 1; i < n; i++){
    std::cout<<", "<<vec[i];
  }
  std::cout<<" ]\n";
}



int main (int argc, char const* argv[])
{
  int n=12;
    
  std::vector<int> v(n);
  for (int i =0;i<n;i++){
    v[i]=i+1;  
  }
    
  int best_f = INT_MAX;
  QAP::Fitness f("1.dat");
  long tot = 0;
  long mm = 479001600;
  do {
    tot++;
    QAP::Solution * s = new QAP::Solution(v.data(),n);
    int  tf = f.f(s);
    if (tf<best_f){
      best_f =tf;
      cout<<(int)(100*(double)tot/mm)<<"% : "<<tf<<" ("<<tot<<")"<<" - ";
      print(s);
    }
    delete s;
    
  } while (std::next_permutation(v.begin(), v.end()));
  cout<<"Best: "<<best_f<<endl;
  return 0;
}
