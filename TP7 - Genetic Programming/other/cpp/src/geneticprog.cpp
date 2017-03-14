#include "geneticprog.hpp"
#include <cstdint>

using namespace GP;

template <typename Numeric>
Block<Numeric>::Block(std::string name){
  name_=name;
}

template <typename Numeric>
std::string Block<Numeric>::name(){
  return name_;
}
template <typename Numeric>
Constant<Numeric>::Constant(Numeric value):
Block<Numeric>(std::to_string(value))
{
  value_= value;
}

template <typename Numeric>
Numeric Constant<Numeric>::value(std::vector<Block<Numeric>> &stack){
  stack.push_back(value_);
  return value_;
}

template <typename Numeric>
Function<Numeric>::Function(Numeric (*f)(Numeric), std::string name):
Block<Numeric>(name)
{
  function=f;
}

template <typename Numeric>
Numeric Function<Numeric>::value(std::vector<Block<Numeric>> &stack)
{
    Numeric v = 0;
    uint32_t in = stack.size();
    if (in > 0){
      Numeric x = stack[in-1];
      v = function(x);
      stack[in-1]=v;
    }
    else{
      stack.push_back(v);
    }
    return v;
}
