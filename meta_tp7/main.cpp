#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <vector>
#include <stack>
#include <map>

using namespace std;

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

prog randProg(prog generator,  uint length);
pop generate(prog generator, uint p_length , uint size);

bool exec(prog, vector<bool>, uint &ok);
int test(prog, map<vector<bool>,bool>);
vector<int> test(pop,map<vector<bool>,bool>);

pop selection(pop population, vector<int> fitness);
pop crossover(pop population, double p_c);
pop mutation(pop population, double p_m, prog generator);

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



void print(prog p);
void print_help();
void print_header();

int main(int argc,char **argv){
  srand(time(NULL));
  prog generator= {&AND, &OR, &NOT, &XOR, &V1,&V2, &V3, &V4};

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
    cout<<"Explored Space: "<<iMax*tmax*psize/(pow(generator.size(),best.size()))*100<<" % "<<endl;
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

prog randProg(prog gen, uint length){
  prog p;
  for (uint i=0;i<length;i++){
    uint r = urand(gen.size());
    p.push_back(gen[r]);
  }
  return p;
}

pop generate(prog generator, uint p_length , uint size)
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

  // auto x = p[0];
  // for (uint i =1;i<p.size();i++){
  //   if ((x!= &AND || x!= &OR || x!= &XOR) && x==p[i]){
  //     errs+=1;
  //   }
  //   x=p[i];
  // }
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


pop selection(pop population, vector<int> fitness){
  pop new_p;
  for (uint i=0;i<population.size();i++){
    uint i0 = urand(population.size());
    uint i1 = urand(population.size());
    if (fitness[i0]>fitness[i1]){
      new_p.push_back(prog(population[i0]));
    }else{
      new_p.push_back(prog(population[i1]));
    }
  }
  return new_p;
}

pop crossover(pop population, double p_c){
  pop new_p;
  uint n = population.size();
  uint m = population[0].size();
  for (uint i = 0 ;i<n;i+=2){
    prog p1 = population[i];
    prog p2 = population[(i+1)%n];
    if (drand()<p_c){
      uint k = urand(m-1)+1;
      prog pp1 ;
      prog pp2 ;
      pp1.insert(pp1.end(),p1.begin(),p1.begin()+k);
      pp1.insert(pp1.end(),p2.begin()+k,p2.end());

      pp2.insert(pp2.end(),p2.begin(),p2.begin()+k);
      pp2.insert(pp2.end(),p1.begin()+k,p1.end());

      new_p.push_back(pp1);
      new_p.push_back(pp2);
    }else{
      new_p.push_back(p1);
      new_p.push_back(p2);
    }
  }
  return new_p;
}

pop mutation(pop population, double p_m, prog generator){
  pop new_p;
  uint n = generator.size();
  for (prog x : population){
    prog p=prog(x);
    for (uint i=0;i<p.size();i++){
      if (drand()<p_m){
        uint k = urand(n);
        p[i]=generator[k];
      }
    }
    new_p.push_back(p);
  }
  return new_p;
}
