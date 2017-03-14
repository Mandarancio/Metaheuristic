#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <vector>
#include <stack>
#include <map>

#include "exmath.hpp"
#include "matplotlibcpp.hpp"
#include "histo.hpp"

using namespace std;
namespace plt = matplotlibcpp;

enum SETTYPE {
  FUNCTIONSET, TERMINALSET
};

typedef vector<bool (*)(stack<bool>&,vector<bool>)>  prog;
typedef unsigned int uint;
typedef vector<prog> pop;

bool AND(stack<bool> &, vector<bool>);
bool OR(stack<bool> &, vector<bool>);
bool NOT(stack<bool> &, vector<bool>);
bool XOR(stack<bool> &, vector<bool>);

bool V1(stack<bool> &, vector<bool>);
bool V2(stack<bool> &, vector<bool>);
bool V3(stack<bool> &, vector<bool>);
bool V4(stack<bool> &, vector<bool>);

prog randProg(map<SETTYPE, prog> ,  uint length);
pop generate(map<SETTYPE, prog> , uint p_length , uint size);

bool exec(prog, vector<bool>, uint &ok);
int test(prog, map<vector<bool>,bool>);
vector<int> test(pop,map<vector<bool>,bool>);


uint max(vector<int>);
uint min(vector<int>);
double avg(vector<int>);
double STD(vector<int>);
uint count(vector<int>,int);

void print(prog p);
void print_help();
void plot(vector<int>);

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
  uint size = 1000;
  uint plength = 10;
  for (int i = 1; i<argc;i++){
    if (!strcmp(argv[i],"-size")){
      size = atoi(argv[++i]);
    }else if (!strcmp(argv[i],"-plength")){
      plength = atoi(argv[++i]);
    }else if (!strcmp(argv[i],"-help")){
      print_help();
      return 0;
    }
  }


  pop landscape = generate(generator, plength,size);
  vector<int> fs = test(landscape,table);

  clog<<"Max: "<<fs[max(fs)]<<endl
      <<"Min: "<<fs[min(fs)]<<endl
      <<"Mean: "<<avg(fs)<<endl
      <<"STD: "<<STD(fs)<<endl
      <<endl<<"----"<<endl
      <<"Size: "<<size<<endl
      <<"Plength: "<<plength<<endl;
  cout<<fs[0];
  for (uint i=1;i<fs.size();i++){
    cout<<","<<fs[i];
  }
  plot(fs);
  return 0;
}


void print_help(){
  cout<<"landscape help:\n"
      <<" -help         Show this help\n"
      <<" -size [1000]  Set the landscape size\n"
      <<" -plength [10] Set the program length\n";
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


bool AND(stack<bool> &s, vector<bool>v){
  if (s.size()<2){
    return false;
  }
  bool a = s.top();
  s.pop();
  bool b = s.top();
  s.pop();
  s.push(a&&b);
  return true;
}

bool OR(stack<bool> &s, vector<bool>v){
  if (s.size()<2){
    return false;
  }
  bool a = s.top();
  s.pop();
  bool b = s.top();
  s.pop();
  s.push(a||b);
  return true;
}

bool NOT(stack<bool> &s, vector<bool>v){
  if (s.size()<1){
    return false;
  }
  bool a = s.top();
  s.pop();
  s.push(!a);
  return true;
}

bool XOR(stack<bool> &s, vector<bool>v){
    if (s.size()<2){
      return false;
    }
    bool a = s.top();
    s.pop();
    bool b = s.top();
    s.pop();
    s.push(a^b);
    return true;
}

bool V1(stack<bool> &s, vector<bool>v){
  s.push(v[0]);
  return true;
}
bool V2(stack<bool> &s, vector<bool>v){
  s.push(v[1]);
  return true;
}
bool V3(stack<bool> &s, vector<bool>v){
  s.push(v[2]);
  return true;
}
bool V4(stack<bool> &s, vector<bool>v){
  s.push(v[3]);
  return true;
}

uint urand(uint max){
  return rand()%max;
}

double drand(){
  return (double)rand()/RAND_MAX;
}

prog randProg(map<SETTYPE,prog> gen, uint length){
  prog p;
  for (uint i=0;i<length;i++){
    if (drand()<0.5){
      uint r = urand(gen[FUNCTIONSET].size());
      p.push_back(gen[FUNCTIONSET][r]);
    }
    else{
      uint r = urand(gen[TERMINALSET].size());
      p.push_back(gen[TERMINALSET][r]);
    }
  }
  return p;
}

pop generate(map<SETTYPE,prog> generator, uint p_length , uint size)
{
  pop p;
  for (uint i = 0 ;i<size;i++){
    p.push_back(randProg(generator, p_length));
  }
  return p;
}


bool exec(prog p, vector<bool> v, uint &ok){
  ok=0;
  stack<bool> s;
  for (uint i=0;i<p.size();i++){
    if (!p[i](s, v)){
      ok++;
    }
  }
  if (s.size()){
    ok+= (s.size()-1);
    return s.top();
  }
  ok=p.size();
  return false;
}


int test(prog p, map<vector<bool>,bool> dataset){
  int res = 0;
  int errs = 0;

  for (auto& kv : dataset) {
    uint ok = 0;
    bool r =exec(p,kv.first,ok);
    if (r!=kv.second){
      res--;
    }
    errs += ok;
  }
  return res *(1+ errs);
}


vector<int> test(pop ps,map<vector<bool>,bool> dataset){
  vector<int> v;
  for (prog p: ps){
    v.push_back(test(p,dataset));
  }
  return v;
}


map<bool (*)(stack<bool>&,vector<bool>), string> names={
  {&AND, "and"},
  {&OR, "or"},
  {&NOT, "not"},
  {&XOR, "xor"},
  {&V1, "V1"},
  {&V2, "V2"},
  {&V3, "V3"},
  {&V4, "V4"}
};

void print(prog p){
  for (auto x: p){
    cout<<names[x]<<" ";
  }
  cout<<endl;
}

void plot(vector<int> fs){
  plt::named_plot("landscape",fs,"x");

  double mean = avg(fs);
  double sigma = STD(fs);
  int N = fs.size();

  plt::named_plot("average",{0.,(double)N},{mean,mean},"r--");
  plt::named_plot("std deviations",{0.,(double)N},{mean+sigma,mean+sigma},"g--");
  plt::plot({0.,(double)N},{mean-sigma,mean-sigma},"g--");

  double *ylims = plt::ylim();
  std::vector<double>*hist = hh::histo(fs,15);
  double alpha = *std::max_element(hist[1].begin(),hist[1].end())*1.1;
  plt::named_plot("fitness distribution",hist[1],hist[0],"r");
  std::vector<double>x=math::lin_space(ylims[0],ylims[1]);
  std::vector<double>y=math::std_dist(alpha,mean,sigma,x);
  plt::named_plot("gaussian fit",y,x,"k--");
  plt::xlabel("t");
  plt::ylabel("fitness");
  plt::title("GP Landscape");
  plt::legend();
  plt::show();

}
