#ifndef GENETICALG_HPP
#define GENETICALG_HPP
#include <eigen3/Eigen/Sparse>
#include <cstdint>
#include <string>

namespace eig = Eigen;

namespace GA{
  struct limits{
    double min;
    double max;
  };

  eig::Matrix<bool, eig::Dynamic, 1> double2bits(double f, const uint32_t n, limits lim);
  double bits2double(eig::Matrix<bool, eig::Dynamic, 1> bits, limits lim);

  // class Solution{
  // public:
  //   Solution(eig::Matrix<bool, eig::Dynamic, 1> value, double (*f)(eig::Matrix<bool, eig::Dynamic, 1>));
  //   ~Solution();

  //   double fitness();
  //   double value();

  //   std::string toString();
  // private:
  //   eig::Matrix<bool, eig::Dynamic, 1> value_;
  // };


};

#endif
