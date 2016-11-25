#include <iostream>
#include "matrix.hpp"
#include "exmath.hpp"
#include <ctime>

int main(int argc, char *argv[])
{
  try{
    std::vector<int> v(3*2);
    v[0]=2;
    v[1]=2;
    v[2]=2;
    v[3]=1;
    v[4]=2;
    v[5]=2;

    math::Matrix<int>a(3,2,v);
    math::Vector<int>b(4,1);
    std::cout<< a.toString()<<std::endl;
    std::cout<< b.toString()<<std::endl;
    std::cout<<"><><><><><\n";
    std::cout<< a.row(1).toString()<<std::endl;
    std::cout<< a.column(1).toString()<<std::endl;
    math::Vector<int> c = b;
    std::cout<<c.toString()<<std::endl;
    std::cout<<c[0]<<std::endl;
    // delete a;
    // delete b;
    std::cout<<"\nTest Performance\n";
    math::Matrix<double> x = math::r(100,100);
    double t=clock();
    math::Matrix<double> y = x*x*x*x*x*x;
    t=clock()-t;
    double millit = 1000.*(t)/CLOCKS_PER_SEC;
    std::cout<<"Execution Time: "<<millit<<" ms\n";
  }catch(int e)
  {
    std::cout<<"Error: "<<e<<std::endl;
    return -1;
  }
  return 0;
}
