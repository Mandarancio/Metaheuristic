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
  ~GroupKnowledge();
  
  double Q();
  
  void accumulateDelta(double delta, int i, int j);
  void resetDelta();
  void updatePherormones();
  void resetPherormones();
  
  int n();
  meta::ASolution * fromItinerary(int * itinerary);

  int* ids;
  double** visibility;
  double** pherormones;
  double** delta_ph; 
  double** probs;
  
private:
  void computeVisibility(int i, int j);
  
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
  ~Ant();
  
  double L();
  double ph(int i, int j);
  int* walk(int start_i);
  void updateDelta();
private:
  int chooseNext(int i);
  GroupKnowledge * gk_;
  int id_;
  int n_;
  double length_;
  int* visitedcity_;
  int* J_;
};

class AntSystem: public meta::AMeta
{
public:
  AntSystem(meta::ASolution * startSolution, GroupKnowledge * gk,int n_ants = 0,int max_t=50);
  ~AntSystem();
  
  virtual meta::ASolution * step(meta::ASolution * sol);
  virtual meta::ASolution * run();
  virtual void reset(meta::ASolution * sol);
private:
  int n_ants_;
  GroupKnowledge * gk_;
  std::vector<Ant*> ants_;
  int max_t_;
};
};

#endif
