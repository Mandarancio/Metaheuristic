#include "exmath.hpp"
#include "img_loader.hpp"
#include "matrix.hpp"
#include "nn.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argc, char *argv[]) {
  srand(time(NULL));
  Loader imgs("X.data", "Y.data");
  std::cout << "Test NN 0\n";
  math::Vector<double> r = imgs.imgAsVector(rand() % imgs.n());
  // math::r(400);
  int levels[3] = {400, 25, 1};
  nn::NeuralNetwork NN(3, levels);
  try {
    double t = clock();
    math::Vector<double> x = NN.evaluate(r);
    t = clock() - t;
    std::cout << x.toString() << std::endl;
    double millit = 1000. * (t) / CLOCKS_PER_SEC;
    std::cout << "Execution Time: " << millit << " ms\n";
  } catch (int err) {
    std::cout << "ERROR: " << err << std::endl;
  }
  return 0;
}
