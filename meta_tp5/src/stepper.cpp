#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "display.hpp"
#include "exmath.hpp"
#include "meta.hpp"
#include "pso.hpp"

#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;

double f2(double x, double y) {
  return -(exp(-x * x / 81) * exp(-y * y / 81) + 0.2 * cos(x) * cos(y));
}

double f(eig::VectorXd x) { return f2(x(0), x(1)); }

void plot(std::vector<double> xs, std::vector<double> ys,
          std::vector<std::vector<double>> zs,
          std::vector<pso::Particle<meta::RnSolution> *> ps, int id) {
  plt::figure();
  plt::contour(xs, ys, zs);

  for (unsigned int i = 0; i < ps.size(); i++) {
    double x = ps[i]->current_position()->solution()(0);
    double y = ps[i]->current_position()->solution()(1);
    double sx = ps[i]->speed()(0);
    double sy = ps[i]->speed()(1);
    plt::plot({x}, {y}, "o");
    plt::arrow(x, y, sx, sy, 0.2, 0.6);
  }
  plt::title("Iteration " + std::to_string(id));
  plt::save("plots/step" + std::to_string(id) + ".png");
  plt::close();
}

int main(int argc, char *argv[]) {
  int tmax = 50;
  int nparticle = 10;
  int n = 2;
  srand(time(NULL));

  meta::RnSolution *r;
  r = new meta::RnSolution(n, eig::VectorXd::Constant(2, -9),
                           eig::VectorXd::Constant(2, 9), f);

  ok("Ready to Go");
  std::cout << r->to_string() << std::endl;
  pso::PSO<meta::RnSolution> *meta =
      new pso::PSO<meta::RnSolution>(r, nparticle, tmax, 0.92, 0.2, 0.18, 0.8);
  std::vector<double> xs, ys;
  std::vector<std::vector<double>> zs;

  for (double x = -9; x <= 9; x += 0.05) {
    xs.push_back(x);
    ys.push_back(x);
  }
  for (unsigned int i = 0; i < xs.size(); i++) {
    zs.push_back(std::vector<double>());
    double x = xs[i];
    for (unsigned int j = 0; j < ys.size(); j++) {
      double y = ys[j];
      double z = f2(x, y);
      zs[i].push_back(z);
    }
  }
  double t1 = 0;
  double t0;

  meta::ASolution *best = r->clone();
  meta->setBest_fitness(r->fitness());
  for (int i = 0; i < tmax; i++) {
    t0 = clock();

    std::vector<pso::Particle<meta::RnSolution> *> ps = meta->particles();
    t1 += clock() - t0;

    plot(xs, ys, zs, ps, i);
    meta::ASolution *next = meta->step(best);
    if (next != best) {
      best = next;
    }
  }
  double millit = 1000. * (t1) / CLOCKS_PER_SEC;
  std::vector<pso::Particle<meta::RnSolution> *> ps = meta->particles();
  display("Execution Time", millit, "ms");
  plot(xs, ys, zs, ps, tmax);

  std::cout << best->to_string() << std::endl;

  plt::show();
}
