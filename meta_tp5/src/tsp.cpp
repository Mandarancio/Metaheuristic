#include "tsp.hpp"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace tsp;

City::City(std::string name, float x, float y) : x_(x), y_(y), name_(name) {}

float City::x() { return x_; }

float City::y() { return y_; }

std::string City::name() { return name_; }

double City::distance(City c) {
  double norm2 = pow(c.x() - x_, 2) + pow(c.y() - y_, 2);
  return sqrt(norm2);
}

Solution::Solution(std::vector<City> array, bool loop)
    : ASolution(), cities_(array), loop_(loop) {}
Solution::~Solution() { cities_.clear(); }

double Solution::delta_fitness(int i, int j) {
  City cj = cities_[j];
  City ci = cities_[i];
  int n = this->n();
  double delta = 0;
  for (int k = -1; k <= 1; k += 2) {
    int ik = (i + k) % n;
    int jk = (j + k) % n;
    ik = ik < 0 ? n + ik : ik;
    jk = jk < 0 ? n + jk : jk;

    if (ik != j) {
      delta += cities_[ik].distance(cj) - cities_[ik].distance(ci);
    }
    if (jk != i) {
      delta += cities_[jk].distance(ci) - cities_[jk].distance(cj);
    }
  }
  return delta;
}

double Solution::fitness() {
  double d = 0;
  unsigned int n = cities_.size();
  for (unsigned int i = 0; i < (loop_ ? n : n - 1); i++) {
    d += cities_[i].distance(cities_[(i + 1) % n]);
  }
  return d;
}

bool Solution::loop() { return loop_; }

std::vector<City> Solution::cities() { return cities_; }

meta::ASolution *Solution::neighbour(int i, int j) {
  std::vector<City> copy(cities_);
  copy[i] = cities_[j];
  copy[j] = cities_[i];
  return new Solution(copy, loop_);
}

std::vector<meta::ASolution *> Solution::neighbours() {
  std::vector<meta::ASolution *> neighbours;
  for (unsigned int i = 0; i < cities_.size() - 1; i++) {
    for (unsigned int j = i + 1; j < cities_.size(); j++) {
      neighbours.push_back(neighbour(i, j));
    }
  }
  return neighbours;
}

meta::ASolution *Solution::random() {
  int size = cities_.size();
  meta::ASolution *now = neighbour(0, 0);
  for (int i = 0; i < 10 * size; i++) {
    meta::ASolution *next = now->rand_neighbour();
    delete now;
    now = next;
  }
  return now;
}

meta::ASolution *Solution::rand_neighbour() {
  int size = n();
  int x = rand() % size;
  int y = rand() % size;
  while (x == y) {
    y = rand() % size;
  }
  return neighbour(x, y);
}

int Solution::n() { return cities_.size(); }

Solution *tsp::fromFile(std::string path, bool loop) {
  std::ifstream fin(path.c_str());
  std::vector<City> cities;
  std::string line;
  while (std::getline(fin, line)) {
    std::istringstream iss(line);
    std::string name;
    float x, y;
    iss >> name >> x >> y;
    cities.push_back(City(name, x, y));
  }
  return new Solution(cities, loop);
}

Solution *tsp::randomFromFile(std::string path, bool loop) {
  std::ifstream fin(path.c_str());
  std::vector<City> cities;
  std::string line;
  while (std::getline(fin, line)) {
    std::istringstream iss(line);
    std::string name;
    float x, y;
    iss >> name >> x >> y;
    cities.push_back(City(name, x, y));
  }
  int size = cities.size();
  for (int i = 0; i < 10 * size; i++) {
    int x = rand() % size;
    int y = rand() % size;
    while (x == y) {
      y = rand() % size;
    }
    City a = cities[x];
    City b = cities[y];
    cities[x] = b;
    cities[y] = a;
  }
  return new Solution(cities, loop);
}

double Solution::sub_fitness(int i, int j) {
  return cities_[i].distance(cities_[j]);
}

meta::ASolution *Solution::create(std::vector<int> is) {
  std::vector<City> cities;
  for (unsigned int i = 0; i < is.size(); i++) {
    cities.push_back(cities_[is[i]]);
  }
  return new Solution(cities, loop_);
}

meta::ASolution *Solution::sub_solution(int i, int j) {
  std::vector<City> cities;
  cities.push_back(cities_[i]);
  cities.push_back(cities_[j]);
  return new Solution(cities, false);
}

std::string Solution::to_string() {
  std::stringstream bff;
  bff << cities_[0].name();
  for (int i = 1; i < n(); i++) {
    bff << "," << cities_[i].name();
  }
  return bff.str();
}
