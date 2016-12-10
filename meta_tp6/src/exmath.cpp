#include "exmath.hpp"
#include <algorithm>
#include <cmath>

#define PI 3.1415926535

using namespace math;

double math::gaussian(double alpha, double mu, double sigma, double x) {
  return alpha * exp(-pow(x - mu, 2) / (2 * sigma * sigma));
}

std::vector<double> math::std_dist(double alpha, double mu, double sigma,
                                   std::vector<double> xs) {
  std::vector<double> y;
  for (uint32_t i = 0; i < xs.size(); i++) {
    y.push_back(math::gaussian(alpha, mu, sigma, xs[i]));
  }
  return y;
}

std::vector<double> math::lin_space(double min, double max, int N) {
  std::vector<double> x;
  double dx = (max - min) / (N - 1);
  for (int i = 0; i < N; i++) {
    x.push_back(min + i * dx);
  }
  return x;
}

double math::sigma(std::vector<double> vs, double mu) {

  double avg = 0;
  for (uint32_t i = 0; i < vs.size(); i++) {
    avg += pow((vs[i] - mu), 2);
  }
  return sqrt(avg / (vs.size() - 1));
}

double math::mean(std::vector<double> vs) {
  double avg = 0;
  for (uint32_t i = 0; i < vs.size(); i++) {
    avg += vs[i];
  }
  return avg / vs.size();
}
double math::sigma(eig::VectorXd vs, double mean) {
  double avg = 0;
  for (uint32_t i = 0; i < vs.size(); i++) {
    avg += pow((vs(i) - mean), 2);
  }
  return sqrt(avg / (vs.size() - 1));
}

std::vector<double> math::scale(std::vector<double> val, double min,
                                double max) {
  double ds = max - min;
  double my_min = *std::min_element(val.begin(), val.end());
  double my_max = *std::max_element(val.begin(), val.end());
  double my_ds = my_max - my_min;
  double scale = ds / my_ds;
  if (my_ds == 0) {
    scale = 1.0;
  }
  std::vector<double> s_val;
  for (uint32_t i = 0; i < val.size(); i++) {
    s_val.push_back((val[i] - my_min) * scale + min);
  }
  return s_val;
}

std::vector<double> math::sum(std::vector<double> x, std::vector<double> y) {
  std::vector<double> z;
  if (x.size() != y.size()) {
    return z;
  }
  for (unsigned int i = 0; i < y.size(); i++) {
    z.push_back(x[i] + y[i]);
  }
  return z;
}

std::vector<double> math::sub(std::vector<double> x, std::vector<double> y) {
  std::vector<double> z;
  if (x.size() != y.size()) {
    return z;
  }
  for (unsigned int i = 0; i < y.size(); i++) {
    z.push_back(x[i] - y[i]);
  }
  return z;
}

std::vector<double> math::mul(double a, std::vector<double> x) {
  std::vector<double> z;
  for (unsigned int i = 0; i < x.size(); i++) {
    z.push_back(x[i] * a);
  }
  return z;
}

double math::r() { return double(rand()) / RAND_MAX; }

double math::sinc(double x) { return x == 0 ? 1 : sin(x) / (x); }
double math::sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }

eig::MatrixXd math::r(uint32_t n, uint32_t m, double scale) {
  return eig::MatrixXd::Random(n, m) * scale;
  // return /x;
}

eig::VectorXd math::r(uint32_t n, double scale) {
  eig::VectorXd x = eig::VectorXd::Random(n) * scale;
  // for (uint32_t i = 0; i < n; i++) {
  // x[i] = r() * scale;
  // }
  return x;
}

double math::pow2(double x) { return x * x; }

// eig::VectorXd math::sigmoid(eig::VectorXd x) {
//   // Vector<double> v();
//   // eig::VectorXd v(x.size());
//   for (uint32_t i = 0; i < x.size(); i++) {
//     x(i) = sigmoid(x(i));
//   }
//   return x;
// }

eig::MatrixXd math::sigmoid(eig::MatrixXd x) {
  // Vector<double> v();
  // eig::MatrixXd v(x.rows(), x.cols());
  for (uint32_t i = 0; i < x.rows(); i++) {
    for (uint32_t j = 0; j < x.cols(); j++) {
      x(i, j) = sigmoid(x(i, j));
    }
  }
  return x; // Matrix<double>(x.rows(), x.columns(), v);
}

eig::MatrixXd math::eye(uint32_t s) {
  eig::MatrixXd x(s, s);
  for (uint32_t i = 0; i < s; i++) {
    x(i, i) = 1.0;
  }
  return x;
}
