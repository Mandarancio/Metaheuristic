#ifndef IMG_LOADER_HPP
#define IMG_LOADER_HPP

#include "matrix.hpp"
#include <string>

class Loader {
public:
  Loader(std::string i_path, std::string label_path);
  math::Matrix<double> img(uint32_t id);
  math::Vector<double> imgAsVector(uint32_t id);
  double label(uint32_t id);
  uint32_t n();

private:
  uint32_t n_;
  math::Vector<double> labels_;
  std::vector<math::Vector<double>> imgs_;
  std::vector<double> bias_;
  std::vector<uint32_t> sizes_;
};
#endif
