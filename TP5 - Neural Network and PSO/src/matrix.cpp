#include "matrix.hpp"

#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace math;

template <typename Numeric>
Matrix<Numeric>::Matrix(uint32_t n, uint32_t m, Numeric inital_v)
    : std::vector<Numeric>(n * m), n_(n), m_(m) {
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < m; j++) {
      (*this)[i * m + j] = inital_v;
    }
  }
}

template <typename Numeric>
Matrix<Numeric>::Matrix(uint32_t n, uint32_t m)
    : std::vector<Numeric>(n * m), n_(n), m_(m) {
  for (uint32_t i = 0; i < n; i++) {
    for (uint32_t j = 0; j < m; j++) {
      (*this)[i * m + j] = 0;
    }
  }
}

template <typename Numeric>
Matrix<Numeric>::Matrix(uint32_t n, uint32_t m, std::vector<Numeric> v)
    : std::vector<Numeric>(v), n_(n), m_(m) //,v_(v)
{}

template <typename Numeric> Matrix<Numeric>::~Matrix() { this->clear(); }

template <typename Numeric>
Numeric Matrix<Numeric>::at(uint32_t x, uint32_t y) const {
  return std::vector<Numeric>::at(x * m_ + y);
}

template <typename Numeric>
void Matrix<Numeric>::set(Numeric v, uint32_t x, uint32_t y) {
  if (x < n_ && y < m_) {
    (*this)[x * m_ + y] = v;
  } else {
    throw ERROR;
  }
}

template <typename Numeric> Matrix<Numeric> Matrix<Numeric>::row(uint32_t x) {
  if (x > n_) {
    throw ERROR;
  }
  std::vector<Numeric> r(m_);
  for (uint32_t i = 0; i < m_; i++) {
    r[i] = (*this)[x * m_ + i];
  }
  return Matrix<Numeric>(1, m_, r);
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::column(uint32_t y) {
  if (y > m_) {
    throw ERROR;
  }
  std::vector<Numeric> r(n_);
  for (uint32_t i = 0; i < n_; i++) {
    r[i] = (*this)[y + i * m_];
  }
  return Matrix<Numeric>(n_, 1, r);
}

template <typename Numeric> Matrix<Numeric> Matrix<Numeric>::t() {
  std::vector<Numeric> vt(m_ * n_);
  //#pragma omp parallel for
  for (uint32_t i = 0; i < m_; i++) {
    //#pragma omp parallel for
    for (uint32_t j = 0; j < n_; j++) {
      vt[i * n_ + j] = (*this)[j * m_ + i];
    }
  }
  return Matrix(m_, n_, vt);
}

template <typename Numeric> uint32_t Matrix<Numeric>::rows() const {
  return n_;
}

template <typename Numeric> uint32_t Matrix<Numeric>::columns() const {
  return m_;
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::reshape(uint32_t n, uint32_t m) {
  if (n * m == n_ * m_) {
    return Matrix<Numeric>(n, m, (*this));
  }
  throw ERROR;
}
template <typename Numeric>
void Matrix<Numeric>::resize(uint32_t n, uint32_t m) {
  m_ = m;
  n_ = n;
}

template <typename Numeric> std::string Matrix<Numeric>::toString() {
  std::stringstream bff;
  for (uint32_t i = 0; i < n_; i++) {
    for (uint32_t j = 0; j < m_; j++) {
      bff << " " << (*this)[i * m_ + j];
    }
    bff << "\n";
  }
  return bff.str();
}

template <typename Numeric>
std::string Matrix<Numeric>::toMatFile(std::string name) {
  std::stringstream bff;
  bff << " #name: " << name << "\n";
  bff << " #type: matrix\n";
  bff << " #rows: " << n_ << "\n #columns: " << m_ << "\n";
  for (uint32_t i = 0; i < n_; i++) {
    for (uint32_t j = 0; j < m_; j++) {
      bff << " " << (*this)[i * m_ + j];
    }
    bff << "\n";
  }
  return bff.str();
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::operator+(const Matrix<Numeric> &b) const {
  if (b.n_ != n_ || b.m_ != m_) {
    throw ERROR;
  }
  std::vector<Numeric> v(n_ * m_);
  for (uint32_t i = 0; i < n_ * m_; i++) {
    v[i] = (*this)[i] + b[i];
  }
  return Matrix<Numeric>(n_, m_, v);
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::operator+(const Numeric &b) const {
  std::vector<Numeric> v(n_ * m_);
  for (uint32_t i = 0; i < n_ * m_; i++) {
    v[i] = (*this)[i] + b;
  }
  return Matrix<Numeric>(n_, m_, v);
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::operator-(const Matrix<Numeric> &b) const {
  if (b.n_ != n_ || b.m_ != m_) {
    throw ERROR;
  }
  std::vector<Numeric> v(n_ * m_);
  for (uint32_t i = 0; i < n_ * m_; i++) {
    v[i] = (*this)[i] - b[i];
  }
  return Matrix<Numeric>(n_, m_, v);
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::operator-(const Numeric &b) const {
  std::vector<Numeric> v(n_ * m_);
  for (uint32_t i = 0; i < n_ * m_; i++) {
    v[i] = (*this)[i] - b;
  }
  return Matrix<Numeric>(n_, m_, v);
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::operator*(const Matrix<Numeric> &b) const {
  if (m_ != b.n_) {
    throw ERROR;
  }
  Matrix<Numeric> v(n_, b.m_);
  for (uint32_t i = 0; i < n_; i++) {
    for (uint32_t j = 0; j < b.m_; j++) {
      Numeric acc = 0;
      for (uint32_t k = 0; k < m_; k++) {
        acc += (*this)[i * m_ + k] * b[k * b.m_ + j];
      }
      v[i * b.m_ + j] = acc;
    }
  }
  return v;
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::operator*(const Numeric &b) const {
  std::vector<Numeric> v(n_ * m_);
  for (uint32_t i = 0; i < n_ * m_; i++) {
    v[i] = (*this)[i] * b;
  }
  return Matrix<Numeric>(n_, m_, v);
}

template <typename Numeric>
Matrix<Numeric> Matrix<Numeric>::operator/(const Numeric &b) const {

  std::vector<Numeric> v(n_ * m_);
  // #pragma omp parallel for
  for (uint32_t i = 0; i < n_ * m_; i++) {
    v[i] = (*this)[i] / b;
  }
  return Matrix<Numeric>(n_, m_, v);
}
template <typename Numeric>
Matrix<Numeric> &Matrix<Numeric>::operator=(const Matrix<Numeric> &b) {
  std::vector<Numeric>::clear();
  // std::vector<Numeric> x(b.n_*b.m_);
  // Numeric * x = new Numeric[b.rows()*b.columns()];
  this->m_ = b.m_;
  this->n_ = b.n_;
  for (unsigned int i = 0; i < b.rows() * b.columns(); i++) {
    std::vector<Numeric>::push_back(b[i]);
  }

  // Matrix<Numeric> * a=new Matrix<Numeric>(b.rows(),b.columns(),x);
  return *this;
}

template <typename Numeric>
Vector<Numeric>::Vector(uint32_t n) : Matrix<Numeric>(1, n) {}
template <typename Numeric>
Vector<Numeric>::Vector(uint32_t n, Numeric initial_v)
    : Matrix<Numeric>(1, n, initial_v) {}

template <typename Numeric>
Vector<Numeric>::Vector(uint32_t n, std::vector<Numeric> v)
    : Matrix<Numeric>(1, n, v) {}

template <typename Numeric>
Vector<Numeric>::Vector(std::vector<Numeric> v)
    : Matrix<Numeric>(1, v.size(), v) {}

template <typename Numeric> Vector<Numeric>::~Vector() {
  // Matrix<Numeric>::~Matrix();
}

template <typename Numeric>
Vector<Numeric> Vector<Numeric>::subvector(uint32_t n, uint32_t m) {
  if (n >= m || m > this->size()) {
    throw ERROR;
  }
  uint32_t d = m - n;
  std::vector<Numeric> v(d);
  std::copy(this->begin() + n, this->begin() + m, v.begin());
  return Vector<Numeric>(d, v);
}

template <typename Numeric> Matrix<Numeric> Vector<Numeric>::t() {
  return Matrix<Numeric>(this->columns(), this->rows(), (*this));
}

template <typename Numeric> Numeric Vector<Numeric>::at(uint32_t i) const {
  return std::vector<Numeric>::at(i);
}

template <typename Numeric> void Vector<Numeric>::set(Numeric x, uint32_t i) {
  Matrix<Numeric>::set(x, 0, i);
}

template <typename Numeric>
Vector<Numeric> Vector<Numeric>::operator-(const Vector<Numeric> &b) const {
  if (b.size() != this->size()) {
    throw ERROR;
  }
  std::vector<Numeric> v(this->size());
  for (uint32_t i = 0; i < b.size(); i++) {
    v[i] = (*this)[i] - b[i];
  }
  return Vector<Numeric>(this->size(), v);
}

template <typename Numeric>
Vector<Numeric> Vector<Numeric>::operator+(const Vector<Numeric> &b) const {
  if (b.size() != this->size()) {
    throw ERROR;
  }
  std::vector<Numeric> v(this->size());
  for (uint32_t i = 0; i < b.size(); i++) {
    v[i] = (*this)[i] + b[i];
  }
  return Vector<Numeric>(this->size(), v);
}

template <typename Numeric>
Vector<Numeric> Vector<Numeric>::operator-(const Numeric &b) const {
  std::vector<Numeric> v(this->size());
  for (uint32_t i = 0; i < this->size(); i++) {
    v[i] = (*this)[i] - b;
  }
  return Vector<Numeric>(this->size(), v);
}

template <typename Numeric>
Vector<Numeric> Vector<Numeric>::operator+(const Numeric &b) const {
  std::vector<Numeric> v(this->size());
  for (uint32_t i = 0; i < this->size(); i++) {
    v[i] = (*this)[i] + b;
  }
  return Vector<Numeric>(this->size(), v);
}

template <typename Numeric>
Vector<Numeric> Vector<Numeric>::operator*(const Numeric &b) const {
  std::vector<Numeric> v(this->size());
  for (uint32_t i = 0; i < this->size(); i++) {
    v[i] = (*this)[i] * b;
  }
  return Vector<Numeric>(this->size(), v);
}
template <typename Numeric>
Vector<Numeric> Vector<Numeric>::operator/(const Numeric &b) const {
  std::vector<Numeric> v(this->size());
  for (uint32_t i = 0; i < this->size(); i++) {
    v[i] = (*this)[i] / b;
  }
  return Vector<Numeric>(this->size(), v);
}

template <typename Numeric>
Vector<Numeric> &Vector<Numeric>::operator=(const Vector<Numeric> &b) {
  std::vector<Numeric>::clear();
  this->m_ = b.m_;
  this->n_ = b.n_;
  for (unsigned int i = 0; i < b.size(); i++) {
    std::vector<Numeric>::push_back(b[i]);
  }

  return *this;
}
template <typename Numeric>
Vector<Numeric> Vector<Numeric>::operator*(const Matrix<Numeric> &b) const {
  if (this->size() != b.rows()) {
    throw ERROR;
  }
  std::vector<Numeric> x;
  for (uint32_t i = 0; i < b.columns(); i++) {
    Numeric v = 0;
    for (uint32_t j = 0; j < b.rows(); j++) {
      v += (*this)[j] * b[j * b.columns() + i];
    }
    x.push_back(v);
  }
  return Vector<Numeric>(x);
}

Matrix<double> math::loadFromFile(std::string path) {
  uint32_t n, m;
  std::ifstream fin(path.c_str());
  std::string a, b;
  fin >> a >> a >> b >> b;
  fin >> a >> n >> b >> m;
  std::vector<double> v;
  double x;
  while (fin >> x) {
    v.push_back(x);
  }
  if (v.size() != n * m) {
    throw ERROR;
  }
  return Matrix<double>(n, m, v);
}

template class math::Matrix<double>;
template class math::Matrix<float>;
template class math::Matrix<int>;
template class math::Matrix<bool>;
template class math::Vector<double>;
template class math::Vector<float>;
template class math::Vector<int>;
template class math::Vector<bool>;
