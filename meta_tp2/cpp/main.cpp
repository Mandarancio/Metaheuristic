#include "qap.h"
#include <iostream>
using namespace std;

void print(Solution * s){
  int n = s->n();
  int * vec = s->vec();
  cout<<"[ "<<vec[0];
  for (int i = 1; i < n; i++){
    cout<<", "<<vec[i];
  }
  cout<<" ]\n";
}

int main(int argc, char const *argv[]) {
  int v[3]={1,3,2};
  Solution * s= new Solution(v,3);
  Solution * s1 = s->neighbor(0, 2);
  print(s);
  print(s1);
  return 0;
}
