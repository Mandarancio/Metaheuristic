#ifndef GP_HPP
#define GP_HPP
#include <map>
#include <stack>
#include <vector>

typedef unsigned int uint;

namespace GP{
  enum SETTYPE {
    FUNCTIONSET, TERMINALSET
  };

  typedef std::vector<bool (*)(std::stack<bool>&,std::vector<bool>)>  prog;
  typedef std::vector<prog> pop;

  bool AND(std::stack<bool> &, std::vector<bool>);
  bool OR(std::stack<bool> &, std::vector<bool>);
  bool NOT(std::stack<bool> &, std::vector<bool>);
  bool XOR(std::stack<bool> &, std::vector<bool>);

  bool V1(std::stack<bool> &, std::vector<bool>);
  bool V2(std::stack<bool> &, std::vector<bool>);
  bool V3(std::stack<bool> &, std::vector<bool>);
  bool V4(std::stack<bool> &, std::vector<bool>);

  prog randProg(std::map<SETTYPE, prog> ,  uint length);
  pop generate(std::map<SETTYPE, prog> , uint p_length , uint size);

  bool exec(prog, std::vector<bool>, uint &ok);
  int test(prog, std::map<std::vector<bool>,bool>);
  std::vector<int> test(pop,std::map<std::vector<bool>,bool>);

  pop selection(pop population, std::vector<int> fitness);
  pop crossover(pop population, double p_c);
  pop mutation(pop population, double p_m,std::map<SETTYPE,prog> generator);

  void print(prog p);
};

#endif
