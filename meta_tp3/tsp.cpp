#include "tsp.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace tsp;

City::City(std::string name, float x, float y):
  name_(name), x_(x), y_(y)
{
}

float City::x()
{
  return x_;
}

float City::y()
{
  return y_;
}

std::string City::name()
{
  return name_;
}

double City::distance(City c)
{
  double norm2= pow(c.x()-x_,2)+pow(c.y()-y_,2);
  return sqrt(norm2);
}

Solution::Solution(std::vector<City> array,bool loop):
  cities_(array), loop_(loop), ASolution()
{
}
Solution::~Solution(){
  cities_.clear();
}
double Solution::fitness()
{
  double d=0;
#pragma omp simd
  for (int i = 1;i<cities_.size();i++)
  {
    d+=cities_[i-1].distance(cities_[i]);
  }
  if (loop_)
  {
    d+=cities_[0].distance(cities_[cities_.size()-1]);
  }
  return d;
}

bool Solution::loop()
{
  return loop_;
}

std::vector<City> Solution::cities()
{
  return cities_;
}

meta::ASolution* Solution::neighbour(int i, int j)
{
  std::vector<City> copy(cities_);
  copy[i]=cities_[j];
  copy[j]=cities_[i];
  return new Solution(copy,loop_);
}

std::vector<meta::ASolution*> Solution::neighbours()
{
  std::vector<meta::ASolution*> neighbours;
  for (int i=0;i<cities_.size()-1;i++)
  {
    for (int j=i+1;j<cities_.size();j++)
    {
      neighbours.push_back(neighbour(i,j)); 
    }
  }
  return neighbours;
}

meta::ASolution * Solution::random()
{
  int size = cities_.size();
  meta::ASolution * now = neighbour(0,0);
  for (int i=0;i<10*size;i++){
    meta::ASolution * next = now->rand_neighbour();
    delete now;
    now = next;
  } 
  return now;
}

meta::ASolution * Solution::rand_neighbour(){
  int size = n();
  int x=rand()%size;
  int y=rand()%size;
  while (x==y)
  {
      y=rand()%size;
  }
  return neighbour(x,y);
}

int Solution::n()
{
  return cities_.size();  
}


Solution* tsp::randomFromFile(std::string path, bool loop)
{
  std::ifstream fin(path.c_str());
  std::vector<City> cities;
  std::string line;
  while (std::getline(fin, line)){
    std::istringstream iss(line);
    std::string name;
    float x,y;
    iss>>name>>x>>y;
    cities.push_back(City(name,x,y));
  }
  int size = cities.size();
  for (int i=0;i<10*size;i++){
    int x=rand()%size;
    int y=rand()%size;
    while (x==y){
      y=rand()%size;
    }
    City a = cities[x];
    City b = cities[y];
    cities[x]=b;
    cities[y]=a;
  }
  return new Solution(cities,loop);
}
