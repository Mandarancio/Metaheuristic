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
double math::sigmoid(double x) { return 1.0 / (1 + exp(-x)); }

Matrix<double> math::r(uint32_t n, uint32_t m, double scale) {
  Matrix<double> x(n, m);
  for (uint32_t i = 0; i < n * m; i++) {
    x[i] = r() * scale;
  }
  return x;
}

Vector<double> math::r(uint32_t n, double scale) {
  Vector<double> x(n);
  for (uint32_t i = 0; i < n; i++) {
    x[i] = r() * scale;
  }
  return x;
}

Vector<double> math::sigmoid(Vector<double> x) {
  // Vector<double> v();
  std::vector<double> v;
  for (uint32_t i = 0; i < x.size(); i++) {
    v.push_back(sigmoid(x[i]));
  }
  return Vector<double>(x.size(), v);
}

Matrix<double> math::sigmoid(Matrix<double> x) {
  // Vector<double> v();
  std::vector<double> v;
  for (uint32_t i = 0; i < x.size(); i++) {
    v.push_back(sigmoid(x[i]));
  }
  return Matrix<double>(x.rows(), x.columns(), v);
}
