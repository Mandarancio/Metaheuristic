#include "exmath.hpp"
#include "matrix.hpp"
#include <ctime>
#include <eigen3/Eigen/Dense>
#include <iostream>

namespace eig = Eigen;

int main(int argc, char *argv[]) {
  try {
    std::cout << "\nTest Performance\n";
    // math::Matrix<double> x = math::r(100, 100, 1.);
    // double t = clock();
    // math::Matrix<double> y = x * x * x * x * x * x;
    // t = clock() - t;
    // double millit = 1000. * (t) / CLOCKS_PER_SEC;
    // std::cout << "Execution Time: " << millit << " ms\n";
    eig::MatrixXd b = math::r(100, 100, 1);

    double t = clock();
    eig::MatrixXd c = b * b * b * b * b * b;
    t = clock() - t;
    double millit = 1000. * (t) / CLOCKS_PER_SEC;
    std::cout << "Execution Time: " << millit << " ms\n";
    eig::VectorXd a = eig::VectorXd::Constant(4, 1);
    std::cout << a << std::endl;
    eig::MatrixXd x = a;
    // b.resize(2, 2);
    // a(3) = 2;
    x.resize(2, 2);
    std::cout << x << std::endl;
    // a << 1, 2;
    a.conservativeResize(5);
    a(4) = 2;
    std::cout << a << std::endl;
    std::cout << x.size() << std::endl;
    x(1, 1) = 2;
    eig::MatrixXd e(2, 3);
    e << 3, 1, 3, 3, 2, 1;
    std::cout << "prod" << std::endl;
    std::cout << e << std::endl << x << std::endl << x * e << std::endl;
  } catch (int e) {
    std::cout << "Error: " << e << std::endl;
    return -1;
  }
  return 0;
}
