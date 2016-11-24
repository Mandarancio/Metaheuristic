#ifndef NN_HPP
#define NN_HPP
#include <vector>

namespace nn{
  class NeuralNetwork
  {
  public:
    NeuralNetwork(std::vector<int> levels);
    std::vector<double> evaluate(std::vector<double> input);
    void setTetas(std::vector<double> tetas);
  private:
    std::vector<int> levels_;
    std::vector<std::pair<int, int> > tetas_size_;
    std::vector<double**> tetas_;

  };

};

#endif
