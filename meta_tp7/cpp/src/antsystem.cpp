#include "antsystem.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace as;

GroupKnowledge::GroupKnowledge(meta::ASolution *baseSolution, double t0,
                               double alpha, double beta, double q, double evap)
    : baseSolution_(baseSolution), n_(baseSolution->n()), t0_(t0),
      alpha_(alpha), beta_(beta), q_(q), evap_(evap) {
  // n_ = baseSolution->n();
  delta_ph = new double *[n_];
  pherormones = new double *[n_];
  visibility = new double *[n_];
  ids = new int[n_];
  probs = new double *[n_];
  for (int i = 0; i < n_; i++) {
    delta_ph[i] = new double[n_];
    pherormones[i] = new double[n_];
    visibility[i] = new double[n_];
    probs[i] = new double[n_];
    ids[i] = i;
  }
  resetPherormones();
  resetDelta();
  for (int i = 0; i < n_; i++) {
    for (int j = i; j < n_; j++) {
      computeVisibility(i, j);
      probs[i][j] = pow(t0_, alpha_) * pow(visibility[i][j], beta_);
      probs[j][i] = probs[i][j];
    }
  }
}

GroupKnowledge::~GroupKnowledge() {
  for (int i = 0; i < n_; i++) {
    delete[] delta_ph[i];
    delete[] probs[i];
    delete[] pherormones[i];
    delete[] visibility[i];
  }
  delete[] ids;
  delete[] visibility;
  delete[] delta_ph;
  delete[] pherormones;
  delete[] probs;
}

void GroupKnowledge::accumulateDelta(double delta, int a, int b) {
  delta_ph[a][b] += delta;
  delta_ph[b][a] += delta;
}

void GroupKnowledge::updatePherormones() {
  for (int i = 0; i < n_ - 1; i++) {
    for (int j = i + 1; j < n_; j++) {
      double p = pherormones[i][j];
      p = (1. - evap_) * p + delta_ph[i][j];
      pherormones[j][i] = p;
      pherormones[i][j] = p;
    }
  }
}
void GroupKnowledge::resetPherormones() {
  for (int i = 0; i < n_; i++) {
    for (int j = i; j < n_; j++) {
      delta_ph[i][j] = t0_;
      delta_ph[j][i] = t0_;
      probs[i][j] = pow(t0_, alpha_) * pow(visibility[i][j], beta_);
      probs[j][i] = probs[i][j];
    }
  }
}

void GroupKnowledge::resetDelta() {
  for (int i = 0; i < n_; i++) {
    for (int j = i; j < n_; j++) {
      delta_ph[i][j] = 0;
      delta_ph[j][i] = 0;
    }
  }
}

double GroupKnowledge::Q() { return q_; }

int GroupKnowledge::n() { return n_; }

void GroupKnowledge::computeVisibility(int i, int j) {
  double d = baseSolution_->sub_fitness(i, j);

  visibility[i][j] = 1. / d;
  visibility[j][i] = 1. / d;
}

meta::ASolution *GroupKnowledge::fromItinerary(int *itinerary) {
  std::vector<int> it(itinerary, itinerary + n_);
  return baseSolution_->create(it);
}

Ant::Ant(int id, GroupKnowledge *gk) : gk_(gk), id_(id), length_(0) {
  n_ = gk->n();
  J_ = new int[n_];
  visitedcity_ = new int[n_];
}

Ant::~Ant() {
  delete[] J_;
  delete[] visitedcity_;
}

int Ant::chooseNext(int a) {
  double p_c = 0;
  double r = double(rand()) / RAND_MAX;

  double den = 0;
  for (int l = 0; l < n_; l++) {
    if (J_[l]) {
      den += gk_->probs[a][l];
    }
  }
  for (int i = 0; i < n_; i++) {
    if (J_[i]) {
      int b = i;
      double pcb = gk_->probs[a][b] / den;
      if (r >= p_c && r <= p_c + pcb) {
        return b;
      }
      p_c += pcb;
    }
  }
  return -1;
}

int *Ant::walk(int start_id) {

  J_ = new int[n_];
  visitedcity_[0] = start_id;
  for (int i = 0; i < n_; i++) {
    J_[i] = 1;
  }
  J_[start_id] = 0;
  int a = start_id;
  double l = 0;
  for (int i = 1; i < n_; i++) {
    int b = chooseNext(a);
    visitedcity_[i] = b;
    J_[b] = 0;
    l += 1 / gk_->visibility[a][b];
    a = b;
  }
  int b = visitedcity_[0];
  l += 1. / gk_->visibility[a][b];
  length_ = l;
  return visitedcity_;
}

double Ant::L() { return length_; }

void Ant::updateDelta() {
  double delta = gk_->Q() / length_;
  int a = visitedcity_[0];
  for (int i = 1; i < n_; i++) {
    int b = visitedcity_[i];
    gk_->accumulateDelta(delta, a, b);
    a = visitedcity_[i];
  }
  gk_->accumulateDelta(delta, a, visitedcity_[0]);
}

AntSystem::AntSystem(meta::ASolution *startSolution, GroupKnowledge *gk,
                     int n_ants, int max_t)
    : meta::AMeta(startSolution, "Ant System"), gk_(gk), max_t_(max_t) {
  n_ants_ = n_ants > 0 ? n_ants : gk->n();
  for (int i = 0; i < n_ants_; i++) {
    ants_.push_back(new Ant(i, gk_));
  }
}

AntSystem::~AntSystem() {
  delete gk_;
  for (int i = 0; i < n_ants_; i++) {
    delete ants_[i];
  }
  ants_.clear();
}

meta::ASolution *AntSystem::step(meta::ASolution *sol) {
  int n_ = gk_->n();
  int *m_path;
  int *path = ants_[0]->walk(0);
  m_path = path;
  double min = ants_[0]->L();
  bool rand_start = n_ants_ == gk_->n();
  gk_->resetDelta();

  for (int i = 1; i < n_ants_; i++) {
    int s = rand_start ? i : rand() % n_;
    path = ants_[i]->walk(s);
    double l = ants_[i]->L();
    if (l < min) {
      min = l;
      m_path = path;
    }
    ants_[i]->updateDelta();
  }
  gk_->updatePherormones();
  if (min < sol->fitness()) {
    delete sol;
    return gk_->fromItinerary(m_path);
  }
  return sol;
}

meta::ASolution *AntSystem::run() {
  meta::ASolution *s = startSolution_->clone();
  for (int i = 0; i < max_t_; i++) {
    s = step(s);
  }
  return s;
}

void AntSystem::reset(meta::ASolution *sol) {
  meta::AMeta::reset(sol);
  gk_->resetDelta();
  gk_->resetPherormones();
}
