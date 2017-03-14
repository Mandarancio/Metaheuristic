#include "gp.hpp"
#include <iostream>

using namespace std;
using namespace GP;

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


bool GP::AND(stack<bool> &s, vector<bool>v){
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

bool GP::OR(stack<bool> &s, vector<bool>v){
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

bool GP::NOT(stack<bool> &s, vector<bool>v){
  if (s.size()<1){
    return false;
  }
  bool a = s.top();
  s.pop();
  s.push(!a);
  return true;
}

bool GP::XOR(stack<bool> &s, vector<bool>v){
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

bool GP::V1(stack<bool> &s, vector<bool>v){
  s.push(v[0]);
  return true;
}
bool GP::V2(stack<bool> &s, vector<bool>v){
  s.push(v[1]);
  return true;
}
bool GP::V3(stack<bool> &s, vector<bool>v){
  s.push(v[2]);
  return true;
}
bool GP::V4(stack<bool> &s, vector<bool>v){
  s.push(v[3]);
  return true;
}

uint urand(uint max){
  return rand()%max;
}

double drand(){
  return (double)rand()/RAND_MAX;
}

prog GP::randProg(map<SETTYPE,prog> gen, uint length){
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

pop GP::generate(map<SETTYPE,prog> generator, uint p_length , uint size)
{
  pop p;
  for (uint i = 0 ;i<size;i++){
    p.push_back(randProg(generator, p_length));
  }
  return p;
}


bool GP::exec(prog p, vector<bool> v, uint &ok){
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


int GP::test(prog p, map<vector<bool>,bool> dataset){
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


vector<int> GP::test(pop ps,map<vector<bool>,bool> dataset){
  vector<int> v;
  for (prog p: ps){
    v.push_back(test(p,dataset));
  }
  return v;
}



void GP::print(prog p){
  for (auto x: p){
    cout<<names[x]<<" ";
  }
  cout<<endl;
}


pop GP::selection(pop population, vector<int> fitness){
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

pop GP::crossover(pop population, double p_c){
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

pop GP::mutation(pop population, double p_m, map<SETTYPE,prog> generator){
  pop new_p;
  uint nf = generator[FUNCTIONSET].size();
  uint nt = generator[TERMINALSET].size();
  for (prog x : population){
    prog p=prog(x);
    for (uint i=0;i<p.size();i++){
      if (drand()<p_m/2){
        uint k = urand(nf);
        p[i]=generator[FUNCTIONSET][k];
      }else if (drand()<p_m){
        uint k = urand(nt);
        p[i]=generator[TERMINALSET][k];
      }
    }
    new_p.push_back(p);
  }
  return new_p;
}
