#include "gp.hpp"

using namespace GP;
template <typename Type>
MyStack<Type>::MyStack(){}
  
template <typename Type>
void MyStack<Type>::reset(){
  while (!stack.empty()){
    stack.pop();
  }
}
  
template <typename Type>
unsigned int MyStack<Type>::size(){
  return stack.size();
}
  
template <typename Type>
Type MyStack<Type>::pop(){
  Type v = stack.top();
  stack.pop();
  return v;
}
  
template <typename Type>
void MyStack<Type>::push(Type v)
{
  stack.push(v);
}

template <typename Type>
OP<Type>::OP(std::string name): name_(name){}

template <typename Type>
std::string OP<Type>::str(){
  return name_;
}

AND::AND(): OP<bool>("AND"){}
bool AND::evalue(MyStack<bool> * stack, std::vector<bool> variables){
  if (stack->size()>=2){
    bool v1 = stack->pop();
    bool v2 = stack->pop();
    
    stack->push(v1 && v2);
    return true;
  }
  return false;
}

OR::OR(): OP<bool>("OR"){}
bool OR::evalue(MyStack<bool> * stack, std::vector<bool> variables){
  if (stack->size()>=2){
    bool v1 = stack->pop();
    bool v2 = stack->pop();
    
    stack->push(v1 || v2);
    return true;
  }
  return false;
}

XOR::XOR(): OP<bool>("XOR"){}
bool XOR::evalue(MyStack<bool> * stack, std::vector<bool> variables){
  if (stack->size()>=2){
    bool v1 = stack->pop();
    bool v2 = stack->pop();
    stack->push(!(v1 && v2) && (v1 || v2));
    return true;
  }
  return false;
}


NOT::NOT(): OP<bool>("NOT"){}
bool NOT::evalue(MyStack<bool> * stack, std::vector<bool> variables){
  if (stack->size()>=1){
    bool v1 = stack->pop();
    stack->push(!v1);
    return true;
  }
  return false;
}
template <typename Type>
VAR<Type>::VAR(unsigned int id): OP<Type>("X"+std::to_string(id)), id_(id){}

template <typename Type>
bool VAR<Type>::evalue(MyStack<Type> * stack, std::vector<Type> variables){
  if (id_<variables.size()){
    stack->push(variables[id_]);
    return true;
  }
  return false;
}

template <typename Type> 
PM<Type> * PM<Type>::instance_;

template <typename Type>
PM<Type> *PM<Type>::instance(std::vector<std::vector<Type> > vals, std::map<std::vector<Type>,Type> dataSet)
{
  if (instance_== 0){
    instance_ = new PM<Type>(vals,dataSet);
  }
  return instance_;
}


template <typename Type>
Type PM<Type>::evalue(std::vector<OP<Type>*> program, std::vector<Type> variables, unsigned int &errors){
  errors = 0;
  stack_->reset();
  for (OP<Type>*p: program){
    if (!p->evalue(stack_,variables)){
      errors++;
    }
  }
  if (stack_->size()==0){
    errors++;
    return -1;  
  }
  errors  += stack_->size()-1;
  return stack_->pop();
}

template <typename Type>
PM<Type>::PM(std::vector<std::vector<Type> > data, std::map<std::vector<Type>,Type> dataSet){
  stack_ = new MyStack<Type>();
  dataSet_ = dataSet;
  vals_ = data;
}

template <typename Type>
int PM<Type>::fitness(std::vector<OP<Type>*> prog){
  int f = 0;
  int e = 0;
  for (std::vector<Type> vars : vals_){
    unsigned int te= 0;
    f+= evalue(prog,vars,te)==dataSet_[vars];
    e+=te;
  }
  return (f-dataSet_.size())-e;
}

template class GP::MyStack<bool>;
template class GP::PM<bool>;
template class GP::OP<bool>;
template class GP::VAR<bool>;

