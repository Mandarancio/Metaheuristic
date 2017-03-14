#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <vector>
#include <stack>
#include <map>
#include "gp.hpp"

using namespace std;
using namespace GP;

uint max(vector<int>);
uint min(vector<int>);
double avg(vector<int>);
double STD(vector<int>);
uint count(vector<int>,int);

void print_help();
void print_header();

int main(int argc,char **argv){
  srand(time(NULL));
  map<SETTYPE, prog> generator ={
    {FUNCTIONSET, {&AND, &OR, &NOT, &XOR}},
    {TERMINALSET, {&V1, &V2, &V3, &V4}}
  };

  map<vector<bool>,bool> table={
    {{0,0,0,0},0}, {{0,0,0,1},1}, {{0,0,1,0},0}, {{0,0,1,1},0},
    {{0,1,0,0},0}, {{0,1,0,1},0}, {{0,1,1,0},0}, {{0,1,1,1},1},
    {{1,0,0,0},0}, {{1,0,0,1},1}, {{1,0,1,0},0}, {{1,0,1,1},0},
    {{1,1,0,0},0}, {{1,1,0,1},0}, {{1,1,1,0},0}, {{1,1,1,1},0}
  };
  vector<int> fitness;

  uint tmax = 100;
  uint psize = 100;
  double t = clock();
  prog best;//= population[bi];
  int best_fitness=-1000;
  uint iMax = 100;
  double pm = 0.1;
  double pc = 0.5;
  bool csv = false;
  uint plength = 10;
  for (int i = 1; i<argc;i++){
    if (!strcmp(argv[i],"-pm")){
      pm = atof(argv[++i]);
    }else if (!strcmp(argv[i],"-pc")){
      pc = atof(argv[++i]);
    }else if (!strcmp(argv[i],"-pop")){
      psize = atoi(argv[++i]);
    }else if (!strcmp(argv[i],"-gmax")){
      tmax = atoi(argv[++i]);
    }else if (!strcmp(argv[i],"-csv")){
      csv = true;
    }else if (!strcmp(argv[i],"-imax")){
      iMax = atoi(argv[++i]);
    }else if (!strcmp(argv[i],"-plength")){
      plength = atoi(argv[++i]);
    }else if (!strcmp(argv[i],"-help")){
      print_help();
      return 0;
    }else if (!strcmp(argv[i],"-header")){
      print_header();
      return 0;
    }
  }

  for (uint i = 0 ;i<iMax;i++){
    std::clog<<"\r["<<(i+1)<<"/"<<iMax<<"]"<<flush;
    pop population = generate(generator,  plength,  psize);
    vector<int> fs= test(population,table);

    uint bi;
    uint wi;

    for (uint t = 0 ; t<tmax;t++){
      bi = max(fs);
      int bf = fs[bi];
      prog best = prog(population[bi]);
      population = selection(population,fs);
      population = crossover(population, pc);
      population = mutation(population, pm, generator);
      fs= test(population,table);
      wi = min(fs);
      population[wi]=prog(best);
      fs[wi]=bf;
    }
    bi = max(fs);
    fitness.push_back(fs[bi]);
    if (best_fitness<fs[bi]){
      best = prog(population[bi]);
      best_fitness = fs[bi];
    }
  }
  clog<<endl;

  t= clock()-t;
  t = 1000. * t / CLOCKS_PER_SEC;
  if (!csv){
    print(best);
    cout<<best_fitness<<endl;
    cout<<"Evals: "<<tmax*psize<<endl;
    cout<<"Time: "<<t/iMax<< " ms"<<endl;
    cout<<"Mean: "<<avg(fitness)<<endl;
    cout<<"Count: "<<count(fitness,0)<<endl;
    uint gsize = generator[FUNCTIONSET].size()+generator[TERMINALSET].size();
    cout<<"Explored Space: "<<iMax*tmax*psize/(pow(gsize,best.size()))*100<<" % "<<endl;
  }else{
    uint mi = min(fitness);
    cout<<psize<<","<<tmax<<","<<plength<<","
        <<pc<<","<<pm<<","<<t/iMax<<","
        <<best_fitness<<","<<avg(fitness)<<","
        <<fitness[mi]<<","<<STD(fitness)<<","
        <<count(fitness,0)<<endl;
  }
  return 0;
}


void print_help(){
  cout<<"gp help:\n"
      <<" -help          Show this help\n"
      <<" -header        Print CSV headers\n"
      <<" -pm [0.2]      Set pm\n"
      <<" -pc [0.5]      Set pc\n"
      <<" -plength [10]  Set program lenght\n"
      <<" -pop [100]   Set population size\n"
      <<" -gmax [100]    Set maximum number of generations\n"
      <<" -imax [100]    Set number of test to run"<<endl;
}

void print_header(){
  cout << "'population size','tmax','program length','pc','pm','average t','max fitness',"
  <<"'average fitness','min fitness','std','number of best solutions'"<<endl;
}



uint max(vector<int> x){
  uint i = 0 ;
  int m = x[0];
  for (uint a=1;a<x.size();a++ ){
    if (x[a]>m){
      m=x[a];
      i=a;
    }
  }
  return i;
}

uint min(vector<int> x){
  uint i = 0 ;
  int m = x[0];
  for (uint a=1;a<x.size();a++ ){
    if (x[a]<m){
      m=x[a];
      i=a;
    }
  }
  return i;
}

double avg(vector<int>x){
  double t=0;
  for (auto i : x){
    t+=i;
  }
  return t/x.size();
}

double STD(vector<int> v){
  double m = avg(v);
  double s=0;
  for (auto i : v){
    s+=(i-m)*(i-m);
  }
  return sqrt(s/v.size());
}

uint count(vector<int> v, int x){
  uint c =0;
  for (int p : v){
    if (p==x){
      c++;
    }
  }
  return c;
}
