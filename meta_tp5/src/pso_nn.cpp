#include "display.hpp"
// #include "img_loader.hpp"
#include "exmath.hpp"
#include "mynn.hpp"
#include "pso.hpp"
// #include "rsolution.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  int tmax = atoi(argv[1]);
  int nparticle = atoi(argv[2]);
  srand(time(NULL));

  nn::MyNeuralNetwork *myNN = new nn::MyNeuralNetwork("X.data", "Y.data");

  meta::MyRnSolution *r;
  r = new meta::MyRnSolution(myNN->vecotrializeTetas(), -2, 2, myNN);
  pso::PSO<meta::MyRnSolution> *meta =
      new pso::PSO<meta::MyRnSolution>(r, nparticle, tmax, 0.9, 2, 2, 1.1);
  double t = 0;
  double f = 0;
  double bf = 1.0;
  for (int i = 0; i < 10; i++) {
    double t1 = clock();
    meta::MyRnSolution *best = dynamic_cast<meta::MyRnSolution *>(meta->run());
    t += clock() - t1;
    double x = best->fitness();
    f += x;
    bf = x < bf ? x : bf;
    // std::cout << f << std::endl;
    r = new meta::MyRnSolution(myNN->vecotrializeTetas(), -2, 2, myNN);
    meta->reset(r);
  }
  double millit = 1000. * (t / 10.) / CLOCKS_PER_SEC;
  std::cout << tmax << "," << nparticle << "," << f / 10.0 << "," << bf << ","
            << millit << std::endl;

  return 0;
}
