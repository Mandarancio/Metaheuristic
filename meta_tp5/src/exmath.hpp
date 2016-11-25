#ifndef MATH_H
#define MATH_H
#include "matrix.hpp"
#include <vector>

namespace math {

double gaussian(double alpha, double mu, double sigma, double x);
double mean(std::vector<double> vals);
double sigma(std::vector<double> vals, double mean);
std::vector<double> lin_space(double min, double max, int N = 100);
std::vector<double> std_dist(double alpha, double mu, double sigma,
                             std::vector<double> xs);
std::vector<double> scale(std::vector<double> val, double min, double max);
std::vector<double> sum(std::vector<double> x, std::vector<double> y);
std::vector<double> sub(std::vector<double> x, std::vector<double> y);
std::vector<double> mul(double a, std::vector<double> x);
double r();
Matrix<double> r(uint32_t n, uint32_t m, double scale = 0);
Vector<double> r(uint32_t n, double scale = 0);

double sinc(double x);
double sigmoid(double x);
Vector<double> sigmoid(Vector<double>);
Matrix<double> sigmoid(Matrix<double>);
};

#endif
