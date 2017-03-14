#include "pso.hpp"
#include "exmath.hpp"
#include "mynn.hpp"

using namespace pso;

#include <iostream>

void print(eig::MatrixXd m, std::string label) {
  std::cout << " #name: " << label << "\n"
            << " #type: matrix\n"
            << " #rows: " << m.rows() << "\n"
            << " #columns: " << m.cols() << "\n"
            << m << "\n\n";
}

template <typename T>
Particle<T>::Particle(T *position, double omega, double c1, double c2,
                      double vmax)
    : position_(position), omega_(omega), c1_(c1), c2_(c2), vmax_(vmax) {
  particle_best_ = dynamic_cast<T *>(position->clone());
  speed_ = eig::VectorXd::Random(position_->n()) * vmax;
  best_fitness_ = position->fitness();
  fitness_ = best_fitness_;
  pos_ = position->solution();
  best_pos_ = position->solution();
  min_ = position->min();
  max_ = position->max();
}

template <typename T> Particle<T>::~Particle() {
  delete position_;
  if (particle_best_) {
    delete particle_best_;
  }
}
template <typename T> eig::VectorXd Particle<T>::speed() { return speed_; }
template <typename T> eig::VectorXd Particle<T>::pos() const { return pos_; }
template <typename T> double Particle<T>::current_fitness() { return fitness_; }

template <typename T> T *Particle<T>::current_position() { return position_; }

template <typename T> double Particle<T>::best_fitness() {
  return best_fitness_;
}

template <typename T> T *Particle<T>::best_position() { return particle_best_; }

template <typename T> eig::VectorXd Particle<T>::bounce(eig::VectorXd p) {

  uint32_t n = p.size();
  for (uint32_t i = 0; i < n; i++) {
    double v = p(i);
    double m = min_(i);
    double M = max_(i);
    if (v < m) {
      double x = 0.9 * (v - m);
      v = m - x;
      if (v > M) {
        v = M;
        speed_(i) = 0.2 * speed_(i);

      } else {
        speed_(i) = -0.9 * speed_(i);
      }
    } else if (v > M) {
      double x = 0.9 * (v - M);
      v = M - x;
      if (v < m) {
        v = m;
        speed_(i) = 0.2 * speed_(i);
      } else {
        speed_(i) = -.9 * speed_(i);
      }
    }
    p(i) = v;
  }
  return p;
}

template <typename T> eig::VectorXd Particle<T>::limit(eig::VectorXd s) {
  for (unsigned int i = 0; i < s.cols(); i++) {
    s(i) = s(i) > +vmax_ ? +vmax_ : s(i);
    s(i) = s(i) < -vmax_ ? -vmax_ : s(i);
  }
  return s;
}

template <typename T> double Particle<T>::move(T *group_best) {
  double r1 = math::r();
  double r2 = math::r();
  if (particle_best_ == NULL || group_best == NULL) {
    std::cerr << "Something wrong!!!" << std::endl;
    throw - 30;
  }
  eig::VectorXd bt = best_pos_ - pos_;
  eig::VectorXd bg = group_best->solution() - pos_;
  speed_ = limit(speed_ * omega_ + bt * r1 * c1_ + bg * r2 * c2_);
  pos_ = bounce(pos_ + speed_);
  T *x = dynamic_cast<T *>(position_->create(pos_));
  if (position_ != particle_best_) {
    delete position_;
  }

  double f = x->fitness();
  fitness_ = f;
  if (f < best_fitness_) {
    if (particle_best_ && particle_best_ != group_best) {
      delete particle_best_;
    }
    best_pos_ = pos_;
    particle_best_ = x; // dynamic_cast<T *>(x->clone());
    best_fitness_ = f;
  }

  position_ = x;

  return f;
}

template <typename T>
PSO<T>::PSO(T *startSolution, int n_particle, int tmax, double omega, double c1,
            double c2, double vmax)
    : meta::AMeta(startSolution, "PSO"), omega_(omega), c1_(c1), c2_(c2),
      vmax_(vmax), n_particles_(n_particle), tmax_(tmax) {
  for (int i = 0; i < n_particle; i++) {
    Particle<T> *p = new Particle<T>(dynamic_cast<T *>(startSolution->random()),
                                     omega, c1, c2, vmax);
    particles_.push_back(p);
  }
}
template <typename T> PSO<T>::~PSO() {
  for (int i = 0; i < n_particles_; i++) {
    delete particles_[i];
  }
  delete startSolution_;
}
template <typename T> meta::ASolution *PSO<T>::step(meta::ASolution *sol) {
  T *bs = dynamic_cast<T *>(sol);
  meta::ASolution *next_best = NULL;
  for (int i = 0; i < n_particles_; i++) {
    double f = particles_[i]->move(bs);

    if (f < bf_) {
      bf_ = f;
      next_best = particles_[i]->best_position();
    }
  }
  if (next_best != NULL) {
    return next_best;
  }
  return sol;
}
template <typename T> meta::ASolution *PSO<T>::run() {
  meta::ASolution *best = startSolution_->clone();
  bf_ = startSolution_->fitness();
  for (int i = 0; i < tmax_; i++) {
    meta::ASolution *next = step(best);
    if (next != best) {
      //!!! SEMAPHORE NEED TO SYNC THE DELITION OF OLD BEST
      // if (best) {
      //   delete best;
      // }
      //!!!! THERE IS A SMALL MEMORY LEAK TO SOLVE
      best = next;
    }
  }
  return best;
}

template <typename T> void PSO<T>::reset(meta::ASolution *sol) {
  meta::AMeta::reset(sol);
  for (int i = 0; i < n_particles_; i++) {
    delete particles_[i];
    particles_[i] = new Particle<T>(dynamic_cast<T *>(sol->random()), omega_,
                                    c1_, c2_, vmax_);
  }
}
template <typename T> std::vector<Particle<T> *> PSO<T>::particles() {
  return particles_;
}
template <typename T> double PSO<T>::best_fitness() { return bf_; }
template <typename T> void PSO<T>::setBest_fitness(double x) { bf_ = x; }

template class pso::Particle<meta::RnSolution>;
template class pso::Particle<meta::MyRnSolution>;
template class pso::PSO<meta::RnSolution>;
template class pso::PSO<meta::MyRnSolution>;
