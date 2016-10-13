#include "qap.h"
#include <iostream>
#include <time.h>
#include <cmath>
#include <stdlib.h> 
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


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  QAP::Solution * s= new QAP::Solution(12);
  cout<<"Starting S: ";
  print(s);
  QAP::Fitness *f = new QAP::Fitness("1.dat");
  cout<<"Start fitness: "<<f->f(s)<<endl;
  int bf=-1;
  QAP::Metaheuristic m(f);
  clock_t t;
  int N = 20000;
  t=clock();
  QAP::Solution * best = m.run(s,N,bf);
  t = clock() - t;
  int millit = round(1000.*((double)t)/CLOCKS_PER_SEC);
  cout<<"Best S: ";
  print(best);
  cout<<"Time: "<<millit<<" ms"<<endl;
  cout<<"Time x It: "<<(double)millit/N<<" ms"<<endl;
  cout<<"Best: "<<bf<<endl;
  cout<<"Computed: "<<f->f(best)<<endl;
  delete s;
  return 0;
}
