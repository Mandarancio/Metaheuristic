#include "display.hpp"
// #include "img_loader.hpp"
#include "matrix.hpp"
#include "mynn.hpp"
#include "pso.hpp"
// #include "rsolution.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  int tmax = 30;
  int nparticle = 100;
  // int n = 2;
  srand(time(NULL));

  nn::MyNeuralNetwork *myNN = new nn::MyNeuralNetwork("X.data", "Y.data");

  meta::MyRnSolution *r;
  r = new meta::MyRnSolution(myNN->vecotrializeTetas(), -1, 1, myNN);

  // ok("Ready to Go");
  // display("Teta size", myNN->vecotrializeTetas().size());
  // display("R fitness", r->fitness());
  // display("R size", r->n());
  pso::PSO<meta::MyRnSolution> *meta =
      new pso::PSO<meta::MyRnSolution>(r, nparticle, tmax, 0.9, 2, 2, 0.9);

  double t1 = clock();
  meta::MyRnSolution *best = dynamic_cast<meta::MyRnSolution *>(meta->run());
  t1 = clock() - t1;
  // double millit = 1000. * (t1) / CLOCKS_PER_SEC;
  std::cout << best->solution().toMatFile("psn");
  std::cerr << best->fitness() << std::endl;
  // display("Execution Time", millit, "ms");
  // display("Best fitness", best->fitness());
  return 0;
}
