#ifndef GP_HPP
#define GP_HPP

#include <stack>
#include <vector>
#include <string>
#include <map>

namespace GP{

template <typename Type>
class MyStack{
public:
  MyStack();
  void reset();
  unsigned int size();
  Type pop();
  void push(Type v);  
private:
  std::stack<Type> stack;    
};

template <typename Type>
class OP{
public:
  OP(std::string name);
  virtual bool evalue(MyStack<Type> * stack, std::vector<Type> variables)=0;
  std::string str();
private:
  std::string name_;
};

class AND : public OP<bool>{
public:
  AND();
  virtual bool evalue(MyStack<bool> * stack, std::vector<bool> variables);
};

class OR : public OP<bool>{
public:
  OR();
  virtual bool evalue(MyStack<bool> * stack, std::vector<bool> variables);
};

class NOT : public OP<bool>{
public:
  NOT();
  virtual bool evalue(MyStack<bool> * stack, std::vector<bool> variables);
};

class XOR: public OP<bool>{
public:
  XOR();
  virtual bool evalue(MyStack<bool> * stack, std::vector<bool> variables);  
};

template <typename Type>
class VAR : public OP<Type>{
public:
  VAR(unsigned int id);
  bool evalue(MyStack<Type> * stack, std::vector<Type> variables);
private:
  unsigned int id_;
};

template <typename Type>
class PM{
public:
  static PM<Type> * instance(std::vector<std::vector<Type> > vals,std::map<std::vector<Type>,Type> dataSet);
  Type evalue(std::vector<OP<Type>*> program, std::vector<Type> variables, unsigned int & errors);
  int fitness(std::vector<OP<Type>*> program);
private :
  PM(std::vector<std::vector<Type> > data,std::map<std::vector<Type>,Type> dataSet);
  std::map<std::vector<Type>,Type> dataSet_;
  std::vector<std::vector<Type> > vals_;
  MyStack<Type> * stack_;
  static PM<Type> * instance_ ;
};
};
#endif
