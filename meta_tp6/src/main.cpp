#include <iostream>
#include "geneticalg.hpp"

int main(int argc, char *argv[]){
  std::cout<<"Test:\n";
  GA::limits lim;

  lim.min = 0;
  lim.max = 1024;

  eig::Matrix<bool,eig::Dynamic,1> test=GA::double2bits(234.5,10,lim);

  // test(0)=1;
  std::cout<<test<<std::endl;
  std::cout<<"Res: "<<GA::bits2double (test, lim);
  return 0;
}
