#ifndef IMG_LOADER_HPP
#define IMG_LOADER_HPP
#include <eigen3/Eigen/Dense>
#include <string>
#include <vector>

namespace eig = Eigen;

class Loader {
public:
  Loader(std::string i_path, std::string label_path);
  eig::MatrixXd img(uint32_t id);
  eig::VectorXd imgAsVector(uint32_t id);
  double label(uint32_t id);
  uint32_t n();

private:
  uint32_t n_;
  std::vector<double> labels_;
  std::vector<eig::VectorXd> imgs_;
  std::vector<double> bias_;
  std::vector<uint32_t> sizes_;
};
#endif
