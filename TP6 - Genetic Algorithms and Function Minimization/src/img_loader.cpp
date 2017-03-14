#include "img_loader.hpp"
#include "exmath.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

Loader::Loader(std::string i_path, std::string label_path) : labels_(200, 1) {
  std::ifstream fin(label_path.c_str());
  // labels_ = eig::MatrixXd(200, 1);
  double x;
  int i = 0;
  while (fin >> x) {
    labels_(i, 0) = x;
    i++;
  }
  fin.close();
  // eig::VectorXd(v.size(), v);
  n_ = labels_.size();
  fin = std::ifstream(i_path.c_str());
  std::string line;
  imgs_ = eig::MatrixXd(n_, 400);
  i = 0;
  while (std::getline(fin, line)) {
    std::istringstream iss(line);
    // eig::VectorXd img(400);
    std::string token;
    uint32_t c = 0;
    while (std::getline(iss, token, ',')) {
      x = atof(token.c_str());
      imgs_(i, c) = x;
      c++;
    }
    i++;
    int size = 20;
    sizes_.push_back(size);
    // imgs_.push_back(img);
    bias_.push_back(math::r());
  }
}

eig::MatrixXd Loader::imgs() { return this->imgs_; }

eig::MatrixXd Loader::img(uint32_t id) {
  eig::MatrixXd img = imgs_.row(id);
  img.resize(sizes_[id], sizes_[id]);
  return img;
  ;
}
eig::VectorXd Loader::imgAsVector(uint32_t id) {
  // img.push_back(bias_[id]);
  // img.resize(1, imgx.size() + );
  return imgs_.row(id);
}
eig::MatrixXd Loader::labels() { return labels_; }
double Loader::label(uint32_t id) { return labels_(id); }
uint32_t Loader::n() { return n_; }
