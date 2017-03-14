#include "display.hpp"
// #include "img_loader.hpp"
#include "exmath.hpp"
#include "mynn.hpp"
#include "pso.hpp"
// #include "rsolution.hpp"
#include "matplotlibcpp.hpp"
#include <iostream>
namespace plt = matplotlibcpp;

int main(int argc, char *argv[]) {

  int tmax = 40;
  int nparticle = 20;
  double omega = 0.75;
  double c1 = 1.8;
  double c2 = 1.2;
  double vmax = 0.35;
  std::vector<eig::VectorXd> particles;
  eig::VectorXd avg_fit(tmax);
  eig::VectorXd best_fit(tmax);
  srand(time(NULL));
  for (int i = 0; i < nparticle; i++) {
    particles.push_back(eig::VectorXd(tmax));
  }

  nn::MyNeuralNetwork *myNN = new nn::MyNeuralNetwork("X.data", "Y.data");

  meta::MyRnSolution *r;
  r = new meta::MyRnSolution(eig::VectorXd::Random(401 * 25 + 26) * 5, -5, 5,
                             myNN);

  pso::PSO<meta::MyRnSolution> *meta =
      new pso::PSO<meta::MyRnSolution>(r, nparticle, tmax, omega, c1, c2, vmax);

  meta::ASolution *best = r->clone();
  meta->setBest_fitness(r->fitness());
  for (int i = 0; i < tmax; i++) {

    std::vector<pso::Particle<meta::MyRnSolution> *> ps = meta->particles();

    best = meta->step(best);
    double avg = 0;
    for (int j = 0; j < nparticle; j++) {
      double x = ps[j]->current_fitness();
      particles[j](i) = x;
      avg += x;
    }

    avg_fit(i) = avg /= nparticle;

    best_fit(i) = best->fitness();
  }
  std::cout << best->fitness() << std::endl;
  for (int i = 0; i < nparticle; i++) {
    plt::plot(particles[i], "x:");
  }
  plt::named_plot("Mean Fitness", avg_fit);
  plt::named_plot("Best Fitness", best_fit);
  plt::legend();
  plt::title("Fitness Evolution");
  plt::ylabel("Fitness");
  plt::xlabel("Iteration");
  plt::xlim(0, tmax - 1);
  plt::figure();
  plt::named_plot("Mean Fitness", avg_fit);
  plt::named_plot("Best Fitness", best_fit);
  plt::legend();
  plt::title("Fitness Evolution");
  plt::ylabel("Fitness");
  plt::xlabel("Iteration");
  plt::xlim(0, tmax - 1);
  plt::show();
  return 0;
}
