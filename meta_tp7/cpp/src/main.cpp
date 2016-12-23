#include "exmath.hpp"
#include "geneticalg.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

double conv(double x) { return round(x * 990 / 1023 + 10); }

double fitness(double x, double y) {
  x = conv(x);
  y = conv(y);
  return -fabs(0.5 * x * sin(sqrt(fabs(x)))) -
         fabs(y * sin(30 * sqrt(fabs(x / y))));
}

// 903//917
int main(int argc, char *argv[]) {
  uint32_t bits = 10;
  uint32_t pop = 100;
  uint32_t evals = 100;
  double pm = 0.1;
  double pc = 0.6;
  uint32_t it = 1;
  for (int i = 1; i < argc; i++) {

    if (!strcmp(argv[i], "-pop") && i < argc - 1) {
      pop = atoi(argv[++i]);
    } else if (!strcmp(argv[i], "-evals") && i < argc - 1) {
      evals = atoi(argv[++i]);
    } else if (!strcmp(argv[i], "-pm") && i < argc - 1) {
      pm = atof(argv[++i]);
    } else if (!strcmp(argv[i], "-pc") && i < argc - 1) {
      pc = atof(argv[++i]);
    } else if (!strcmp(argv[i], "-it") && i < argc - 1) {
      it = atoi(argv[++i]);
    }
  }

  srand(time(NULL));
  for (uint32_t i = 0; i < it; i++) {
    GA::limits lim;
    lim.min = 0;
    lim.max = 1023;

    // GA::Element s(903, 916.9, 16, lim, fitness);

    GA::GeneticAlgorithm meta(bits, pop, evals, pc, pm, lim, fitness);

    double t = clock();
    GA::Element *r = meta.run();
    t = clock() - t;
    t = 1000. * t / CLOCKS_PER_SEC;

    std::cout << bits << "," << pop << "," << evals * pop << "," << pc << ","
              << pm << "," << r->values()[0] << "," << r->values()[1] << ","
              << r->fitness() << "," << t << std::endl;
  }
  return 0;
}
