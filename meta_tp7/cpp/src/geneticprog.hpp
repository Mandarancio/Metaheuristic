#ifndef GENETICPROG_HPP
#define GENETICPROG_HPP
#include <vector>
#include <string>

namespace GP{

  template <typename Numeric>
  class Block{
  public:
    Block(std::string name);
    virtual Numeric value(std::vector<Block<Numeric>>& stack) =0;
    std::string name();
  private:
    std::string name_;
  };

  template <typename Numeric>
  class Constant: public Block<Numeric>
  {
  public:
    Constant(Numeric value);
    virtual Numeric value(std::vector<Block<Numeric>> &stack);
  private:
    Numeric value_;
  };

  template <typename Numeric>
  class Function: public Block<Numeric>
  {
  public:
    Function(Numeric (*f)(Numeric), std::string name);
    virtual Numeric value(std::vector<Block<Numeric>> &stack);
  private:
    Numeric (*function)(Numeric);
  };

  template <typename Numeric>
  class Operand: public Block<Numeric>
  {
  public:
    Operand(Numeric(*f)(Numeric, Numeric), std::string name);
    virtual Numeric value(std::vector<Block<Numeric>>& stack);
  private:
    Numeric (*function)(Numeric, Numeric);
  };


};
#endif
