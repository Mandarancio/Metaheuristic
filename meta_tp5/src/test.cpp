#include "exmath.hpp"
#include "img_loader.hpp"
#include "matrix.hpp"
#include "nn.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  Loader l("X.data", "Y.data");
  // std::cout << l.label(0) << std::endl;
  math::Matrix<double> m = math::loadFromFile("psn.mat");
  // std::cout << m.toMatFile("psn") << std::endl;
  math::Vector<double> psn(m.size(), m);
  math::Vector<double> x1 = psn.subvector(0, 25 * 400);
  math::Vector<double> x2 = psn.subvector(25 * 400, 25 * 400 + 25);
  math::Matrix<double> r = math::sigmoid(
      math::sigmoid(math::sigmoid(l.imgAsVector(0).reshape(1, 400)) *
                    x1.reshape(400, 25)) *
      x2.reshape(25, 1));
  std::cout << r.toString() << std::endl;
  // nn::NeuralNetwork nN(std::vector<int>({400, 25, 1}));
  // nN.setTeta(x1, 0);
  // nN.setTeta(x2, 1);
  // // std::cout << x1[0] << " " << x1[2] << std::endl;
  // // std::cout << m[0] << " " << m[2] << std::endl;
  // // std::cout << math::sigmoid(0.5) << std::endl;
  // nN.evaluate(l.imgAsVector(0)); //.toString() << std::endl;
  return 0;
}
