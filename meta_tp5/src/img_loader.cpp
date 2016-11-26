#include "img_loader.hpp"
#include "exmath.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

Loader::Loader(std::string i_path, std::string label_path) : labels_(0) {
  std::ifstream fin(label_path.c_str());

  double x;
  while (fin >> x) {
    labels_.push_back(x);
  }
  fin.close();
  // eig::VectorXd(v.size(), v);
  n_ = labels_.size();
  fin = std::ifstream(i_path.c_str());
  std::string line;
  while (std::getline(fin, line)) {
    std::istringstream iss(line);
    eig::VectorXd img(400);
    std::string token;
    uint32_t c = 0;
    while (std::getline(iss, token, ',')) {
      x = atof(token.c_str());
      img(c) = x;
      c++;
    }
    int size = round(sqrt(img.size()));
    sizes_.push_back(size);
    imgs_.push_back(img);
    bias_.push_back(math::r());
  }
}

eig::MatrixXd Loader::img(uint32_t id) {
  eig::MatrixXd img = imgs_.at(id);
  img.resize(sizes_[id], sizes_[id]);
  return img;
  ;
}
eig::VectorXd Loader::imgAsVector(uint32_t id) {
  eig::VectorXd img = imgs_.at(id);
  // img.push_back(bias_[id]);
  // img.resize(1, img.size() + );
  return img;
}

double Loader::label(uint32_t id) { return labels_.at(id); }
uint32_t Loader::n() { return n_; }
