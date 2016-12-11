#include "geneticalg.hpp"
#include <cmath>

using namespace GA;

eig::Matrix<bool, eig::Dynamic, 1> GA::double2bits(double f, const uint32_t n, limits lim){
  eig::Matrix<bool, eig::Dynamic, 1> bits;
  if (f<lim.min){
    for (uint32_t i=0; i<n;i++){
      bits(i)=0;
    }
  }
  else if (f>lim.max){
    for (uint32_t i=0; i<n;i++){
      bits(i)=1;
    }
  }
  else{
    double size = pow(2,n);
    double dt = (lim.max-lim.min)/size;
    uint32_t d = round((f-lim.min)/dt);
    uint32_t i = 0 ;
    while (d>0){
      uint32_t bit = d%2;
      d = d/2;
      bits(i)=bit;
      i++;
    }
  }
  return bits;
}

double GA::bits2double(eig::Matrix<bool, eig::Dynamic, 1> bits, limits lim){
  uint32_t n =bits.rows();
  double size = pow(2,n);
  double dt = (lim.max-lim.min)/size;

  double v= lim.min;
  for (uint32_t i=0;i<n;i++){
    uint32_t k = n-i-1;
    double x = pow(2,k)*bits(i)*dt;
    v+=x;
  }

  return v;
}

