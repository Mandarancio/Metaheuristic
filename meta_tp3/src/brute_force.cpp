#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>
#include <cmath>

#include "tsp.hpp"
#include "meta.hpp"

using namespace std;
double fact(double n){
  return sqrt(2*M_PI*n)*pow((n/M_E),n);
}


int main(int argc, char *argv[])
{
  if (argc!=2)
  {
    cout<<"brute_force FILE.DAT"<<endl;
    return -1;
  }  
  string path(argv[1]);
  meta::ASolution * s = tsp::fromFile(path);
  int n = s->n();
  std::vector<int> v(n);
  for (int i =0;i<n;i++){
    v[i]=i+1;  
  }
  double best = s->fitness();
  double current = best;
  int iter = 1;
  unsigned long tot = fact(n);
 
  cout<<"Best: "<<best_f<<endl;
  return 0;
}
