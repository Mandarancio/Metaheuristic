#include "img_loader.hpp"
#include "matplotlibcpp.hpp"
#include <iostream>
namespace plt = matplotlibcpp;

void show_img(math::Matrix<double> img) {
  std::vector<std::vector<double>> v;
  std::cout << "Img(" << img.rows() << "," << img.columns() << ")]\n";
  for (uint32_t i = 0; i < img.rows(); i++) {
    std::vector<double> row;
    for (uint32_t j = 0; j < img.columns(); j++) {
      row.push_back(img.at(i, j));
    }
    v.push_back(row);
  }
  plt::imshow(v);
}

int main(int argc, char **argv) {
  Loader l("X.data", "Y.data");
  std::cout << l.n() << std::endl;
  show_img(l.img(rand() % l.n()));
  plt::show();
  return 0;
}
