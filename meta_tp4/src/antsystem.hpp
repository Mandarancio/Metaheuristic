#ifndef ANTSYSTEM_HPP
#define ANTSYSTEM_HPP

#include "meta.hpp"
#include <map>
#include <vector>
#include <string> 

namespace as
{

class GroupKnowledge{
public:
  GroupKnowledge(meta::ASolution * baseSolution, double t0, double alpha, double beta, double q,double evap);
  double alpha();
  double beta();
  double q();
  void updateDelta(double delta, int i, int j);
  void setPherormones(double ph, int i, int j);
  int n();
  meta::ASolution * fromItinerary(int * itinerary);
  void resetDeltas();
  void updatePh();
  int* ids;
  double** visibility;
  double** pherormones;
  double** delta_ph; 
private:
  void computeVisibility(int i, int j);
  void setDelta(double delta,int i,int j);
  meta::ASolution * baseSolution_;
  double alpha_;
  double beta_;
  double q_;
  double t0_;
  double evap_;
  int n_;
  
};

class Ant{
public:
  Ant(int id,GroupKnowledge * gk);
  double L();
  double ph(int i, int j);
  int* walk(int start_i);
  void updateDelta();
private:
  double p(int i, int j);
  bool notInJ(int i);
  int chooseNext(int i);
  GroupKnowledge * gk_;
  int id_;
  int n_;
  double length_;
  int* visitedcity_;
  int* J;
  
  
};

class AntSystem: public meta::AMeta
{
public:
  AntSystem(meta::ASolution * startSolution, GroupKnowledge * gk,int n_ants = 0,int max_t=50);
  virtual meta::ASolution * step(meta::ASolution * sol);
  virtual meta::ASolution * run();
private:
  int n_ants_;
  GroupKnowledge * gk_;
  std::vector<Ant> ants_;
  int max_t_;
};
};

#endif
