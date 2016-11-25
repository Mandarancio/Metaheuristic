#include "img_loader.hpp"
#include "exmath.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

Loader::Loader(std::string i_path, std::string label_path) : labels_(0) {
  std::ifstream fin(label_path.c_str());
  std::vector<double> v;
  double x;
  while (fin >> x) {
    v.push_back(x);
  }
  fin.close();
  labels_ = math::Vector<double>(v.size(), v);
  n_ = v.size();
  fin = std::ifstream(i_path.c_str());
  std::string line;
  while (std::getline(fin, line)) {
    std::istringstream iss(line);
    std::vector<double> img;
    std::string token;

    while (std::getline(iss, token, ',')) {
      x = atof(token.c_str());
      img.push_back(x);
    }
    int size = round(sqrt(img.size()));
    sizes_.push_back(size);
    imgs_.push_back(math::Vector<double>(img.size(), img));
    bias_.push_back(math::r());
  }
}

math::Matrix<double> Loader::img(uint32_t id) {
  return imgs_.at(id).reshape(sizes_[id], sizes_[id]).t();
}
math::Vector<double> Loader::imgAsVector(uint32_t id) {
  math::Vector<double> img = imgs_.at(id);
  // img.push_back(bias_[id]);
  // img.resize(1, img.size() + );
  return img;
}

double Loader::label(uint32_t id) { return labels_.at(id); }
uint32_t Loader::n() { return n_; }
