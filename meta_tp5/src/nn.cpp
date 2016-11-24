#include "nn.hpp"
#include "exmath.hpp"

using namespace nn;

NeuralNetwork::NeuralNetwork(std::vector<int> levels):
levels_(levels)
{
  for (unsigned int i = 0;i<levels.size()-1;i++)
  {
    std::pair<int,int> s(levels[i],levels[i+1]);
    tetas_size_.push_back(s);
    double **teta = new double*[levels[i]];
    for ( int j =0;i<levels[i];j++)
    {
      teta[j]=new double[levels[i+1]];
      for (int k=0;k<levels[i+1];i++)
      {
        teta[j][k]=math::r();
      }
    }
    tetas_.push_back(teta);
  }
}

std::vector<double> NeuralNetwork::evaluate(std::vector<double> input)
{

}
