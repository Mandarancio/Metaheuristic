#include "display.hpp"
#include "exmath.hpp"
#include "histo.hpp"
#include "img_loader.hpp"
#include "mynn.hpp"
// "",#include "rsolution.hpp"
#include <iostream>

#include "matplotlibcpp.hpp"
namespace plt = matplotlibcpp;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "landscape N_TEST" << std::endl;
    return -1;
  }
  srand(time(NULL));
  uint32_t N = std::atoi(argv[1]);
  eig::VectorXd x(N);
  nn::MyNeuralNetwork *myNN = new nn::MyNeuralNetwork("X.data", "Y.data");
  // eig::VectorXd c = eig::VectorXd::Constant(401 * 26 + 26, 5);
  double bf = 1.0;
  double mf = 0;
  for (uint32_t i = 0; i < N; i++) {
    eig::VectorXd t = eig::VectorXd::Random(401 * 25 + 26) * 10; //- c;
    // std::cout << t.minCoeff() << "->" << t.mean() << "<-" << t.maxCoeff()
    //           << std::endl;

    double f = myNN->evalue(t);
    mf += f;
    if (f < bf) {
      bf = f;
    }
    x(i) = f;
  }
  double mean = mf / N;
  double sigma = math::sigma(x, mean);
  std::vector<double> *hist = hh::histo(x, 20);
  double alpha = *std::max_element(hist[1].begin(), hist[1].end()) * 1.1;
  display("Mean", mean);
  display("Best", bf);
  display("Std Deviation", sigma);
  plt::named_plot("f(NN)", x, "x");
  plt::named_plot("Mean", std::vector<double>({0., double(N)}),
                  std::vector<double>({mean, mean}), "r--");
  plt::named_plot("STD", std::vector<double>({0., double(N)}),
                  std::vector<double>({mean + sigma, mean + sigma}), "g--");
  plt::plot(std::vector<double>({0., double(N)}),
            std::vector<double>({mean - sigma, mean - sigma}), "g--");

  plt::named_plot("Distribution", hist[1], hist[0], "r-");
  double *ylims = plt::ylim();
  std::vector<double> xg = math::lin_space(ylims[0], ylims[1]);
  std::vector<double> yg = math::std_dist(alpha, mean, sigma, xg);
  plt::named_plot("gaussian fit", yg, xg, "k--");
  plt::title("Landscape (" + std::to_string(N) + " rand solution)");
  plt::xlabel("iterations");
  plt::ylabel("fitness");
  plt::legend();

  plt::show();

  return 0;
}
