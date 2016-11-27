#include "display.hpp"
// #include "img_loader.hpp"
#include "exmath.hpp"
#include "mynn.hpp"
#include "pso.hpp"
// #include "rsolution.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  int tmax = 10;
  int nparticle = 10;
  double omega = 0.9;
  double c1 = 2.0;
  double c2 = 2.0;
  double vmax = 0.8;
  bool save = false;
  bool save_csv = false;
  for (int i = 0; i < argc; i++) {
    if (std::strcmp(argv[i], "-tmax") == 0 && i + 1 < argc) {
      tmax = atoi(argv[i + 1]);
      i++;
    } else if (std::strcmp(argv[i], "-npart") == 0 && i + 1 < argc) {
      nparticle = atoi(argv[i + 1]);
      i++;
    } else if (std::strcmp(argv[i], "-save") == 0) {
      save = true;
      save_csv = false;
    } else if (std::strcmp(argv[i], "-csv") == 0) {
      save_csv = true;
      save = false;
    } else if (std::strcmp(argv[i], "-omega") == 0 && i + 1 < argc) {
      omega = atof(argv[i + 1]);
      i++;
    } else if (std::strcmp(argv[i], "-c1") == 0 && i + 1 < argc) {
      c1 = atof(argv[i + 1]);
      i++;
    } else if (std::strcmp(argv[i], "-c2") == 0 && i + 1 < argc) {
      c2 = atof(argv[i + 1]);
      i++;
    } else if (std::strcmp(argv[i], "-cx") == 0 && i + 1 < argc) {
      c1 = atof(argv[i + 1]);
      c2 = c1;
      i++;
    } else if (std::strcmp(argv[i], "-c") == 0 && i + 2 < argc) {
      c1 = atof(argv[i + 1]);
      c2 = atof(argv[i + 2]);
      i += 2;
    } else if (std::strcmp(argv[i], "-vmax") == 0 && i + 1 < argc) {
      vmax = atof(argv[i + 1]);
      i++;
    }
  }
  srand(time(NULL));

  nn::MyNeuralNetwork *myNN = new nn::MyNeuralNetwork("X.data", "Y.data");

  meta::MyRnSolution *r;
  r = new meta::MyRnSolution(eig::VectorXd::Random(401 * 25 + 26) * 5, -5, 5,
                             myNN);

  pso::PSO<meta::MyRnSolution> *meta =
      new pso::PSO<meta::MyRnSolution>(r, nparticle, tmax, omega, c1, c2, vmax);
  double t = 0;
  double f = 0;
  double t1 = clock();
  meta::MyRnSolution *best = dynamic_cast<meta::MyRnSolution *>(meta->run());
  t += clock() - t1;
  f = best->fitness();
  double millit = 1000. * (t) / CLOCKS_PER_SEC;
  double prec = myNN->precision(best->solution());
  if (save_csv) {
    std::cout << tmax << "," << nparticle << "," << omega << "," << c1 << ","
              << c2 << "," << vmax << "," << f << "," << prec << "," << millit
              << std::endl;
  } else if (save) {
    std::cout << " #name: precision\n"
              << " #type: matrix\n"
              << " #rows: 1\n"
              << " #columns: 1\n"
              << " " << prec << "\n\n";
    std::cout << " #name: fitness\n"
              << " #type: matrix\n"
              << " #rows: 1\n"
              << " #columns: 1\n"
              << " " << f << "\n\n";
    std::cout << " #name: teta0\n"
              << " #type: matrix\n"
              << " #rows: " << myNN->teta(0).rows() << " \n"
              << " #columns:" << myNN->teta(0).cols() << "\n";
    std::cout << myNN->teta(0) << "\n\n";
    std::cout << " #name: teta1\n"
              << " #type: matrix\n"
              << " #rows: " << myNN->teta(1).rows() << "\n"
              << " #columns: " << myNN->teta(1).cols() << "\n";
    std::cout << myNN->teta(1) << "\n\n";
  }
  return 0;
}
