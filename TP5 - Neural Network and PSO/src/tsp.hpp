#ifndef TSP_HPP
#define TSP_HPP
#include "meta.hpp"
#include <string>
#include <vector>


namespace tsp{
  class City
  {
    public:
      City(std::string name, float x, float y);
      float x();
      float y();
      std::string name();
      double distance(City c);
    private:
      float x_,y_;
      std::string name_;
  };
  
  class Solution: public meta::ASolution
  {
    public:
      Solution(std::vector<City> array,bool loop=true);
      virtual ~Solution();
      virtual double fitness();
      virtual double delta_fitness(int i, int j);
      bool loop();
      std::vector<City> cities();
      virtual meta::ASolution * neighbour(int i, int j);
      virtual std::vector<meta::ASolution*> neighbours();
      virtual meta::ASolution * random();
      virtual meta::ASolution * rand_neighbour();
      virtual meta::ASolution * sub_solution(int i, int j);
      virtual double sub_fitness(int i,int j);
      virtual int n();
      virtual std::string to_string();
      virtual meta::ASolution * create(std::vector<int> is);
    private:
      std::vector<City> cities_;
      bool loop_;
  };
  
  Solution * randomFromFile(std::string path,bool loop=true);
  Solution * fromFile(std::string path, bool loop= true);

};

#endif
