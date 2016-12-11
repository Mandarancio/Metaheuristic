#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstdint>
#include <string>
#include <vector>

#define ERROR 20;

namespace math {
template <typename Numeric> class Matrix : public std::vector<Numeric> {
public:
  Matrix(uint32_t n, uint32_t m, Numeric inital_v);
  Matrix(uint32_t n, uint32_t m);
  Matrix(uint32_t n, uint32_t m, std::vector<Numeric> v);
  Matrix(Matrix<Numeric> *a);
  virtual ~Matrix();

  Matrix<Numeric> row(uint32_t x);
  Matrix<Numeric> column(uint32_t y);

  Numeric at(uint32_t x, uint32_t y) const;
  void set(Numeric v, uint32_t x, uint32_t y);

  virtual Matrix<Numeric> t();

  uint32_t rows() const;
  uint32_t cols() const;

  Matrix<Numeric> reshape(uint32_t n, uint32_t m);
  void resize(uint32_t n, uint32_t m);

  std::string toString();
  std::string toMatFile(std::string name = "mat");
  // std::string toLaTeX();

  Matrix<Numeric> operator+(const Matrix<Numeric> &b) const;
  Matrix<Numeric> operator+(const Numeric &b) const;
  Matrix<Numeric> operator-(const Matrix<Numeric> &b) const;
  Matrix<Numeric> operator-(const Numeric &b) const;
  Matrix<Numeric> operator*(const Matrix<Numeric> &b) const;
  Matrix<Numeric> operator*(const Numeric &b) const;
  Matrix<Numeric> operator/(const Numeric &b) const;
  Matrix<Numeric> &operator=(const Matrix<Numeric> &b);

protected:
  uint32_t n_, m_;
};

template <typename Numeric> class Vector : public Matrix<Numeric> {
public:
  Vector(uint32_t n);
  Vector(uint32_t n, Numeric initial_v);
  Vector(uint32_t n, std::vector<Numeric> v);
  Vector(std::vector<Numeric> v);

  virtual ~Vector();
  Vector<Numeric> subvector(uint32_t n, uint32_t m);
  virtual Matrix<Numeric> t();
  Numeric at(uint32_t i) const;
  void set(Numeric x, uint32_t i);
  Vector<Numeric> operator-(const Vector<Numeric> &b) const;
  Vector<Numeric> operator+(const Vector<Numeric> &b) const;
  Vector<Numeric> operator-(const Numeric &b) const;
  Vector<Numeric> operator+(const Numeric &b) const;
  Vector<Numeric> operator*(const Numeric &b) const;
  Vector<Numeric> operator*(const Matrix<Numeric> &b) const;
  Vector<Numeric> operator/(const Numeric &b) const;
  Vector<Numeric> &operator=(const Vector<Numeric> &b);
};

Matrix<double> loadFromFile(std::string path);
};

#endif
