#include "pso.hpp"
#include "exmath.hpp"
#include "mynn.hpp"

using namespace pso;

template <typename T>
Particle<T>::Particle(T *position, double omega, double c1, double c2,
                      double vmax)
    : position_(position), omega_(omega), c1_(c1), c2_(c2), vmax_(vmax) {
  particle_best_ = dynamic_cast<T *>(position->clone());
  // for (int i = 0; i < position->n(); i++) {
  //   speed_.set(math::r() * 2 * vmax - vmax, i);
  // }
  speed_ = eig::VectorXd::Random(position_->n()) * 2 * vmax -
           eig::VectorXd::Constant(position_->n(), vmax);
}

template <typename T> Particle<T>::~Particle() {
  delete position_;
  if (particle_best_) {
    delete particle_best_;
  }
}
template <typename T> eig::VectorXd Particle<T>::speed() { return speed_; }

template <typename T> double Particle<T>::current_fitness() {
  return position_->fitness();
}

template <typename T> T *Particle<T>::current_position() { return position_; }

template <typename T> double Particle<T>::best_fitness() {
  return particle_best_->fitness();
}

template <typename T> T *Particle<T>::best_position() { return particle_best_; }

template <typename T> eig::VectorXd Particle<T>::bounce(eig::VectorXd p) {
  // double b_factor = 0.9;
  eig::VectorXd M = position_->max();
  eig::VectorXd m = position_->min();
  int n = position_->n();
  // bool unchanged = true;
  for (int i = 0; i < n; i++) {
    double v = p(i);
    if (v < m(i)) {
      double x = 0.9 * (v - m(i));
      v = m(i) - x;
      if (v > M(i)) {
        v = M(i);
        speed_(i) = 0.2 * speed_(i);

      } else {
        speed_(i) = -0.9 * speed_(i);
      } // unchanged = false;
    } else if (v > M(i)) {
      double x = 0.9 * (v - M(i));
      v = M(i) - x; //-b_factor*v;
      if (v < m(i)) {
        v = m(i);
        speed_(i) = 0.2 * speed_(i);
      } else {
        speed_(i) = -.9 * speed_(i);
      }
      // unchanged = false;
      // speed_.set(-0.9 * speed_.at(i), i);
    }
    p(i) = v; //.set(v, i);
  }
  return p;
}

template <typename T> eig::VectorXd Particle<T>::limit(eig::VectorXd s) {
  for (unsigned int i = 0; i < s.cols(); i++) {
    s(i) = s(i) > vmax_ ? s(i) : vmax_;
    s(i) = s(i) < -vmax_ ? s(i) : -vmax_;
  }
  return s;
}

template <typename T> double Particle<T>::move(T *group_best) {
  double r1 = math::r();
  double r2 = math::r();

  eig::VectorXd p = position_->solution();
  eig::VectorXd bt = particle_best_->solution() - p;
  eig::VectorXd bg = group_best->solution() - p;

  speed_ = (speed_ * omega_ + bt * r1 * c1_ + bg * r2 * c2_);
  p = bounce(p + speed_);
  T *x = dynamic_cast<T *>(position_->create(p));
  delete position_;

  double f = x->fitness();
  if (f < particle_best_->fitness()) {
    delete particle_best_;
    particle_best_ = dynamic_cast<T *>(x->clone());
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
}
template <typename T> meta::ASolution *PSO<T>::step(meta::ASolution *sol) {
  double bf = sol->fitness();
  T *bs = dynamic_cast<T *>(sol);
  meta::ASolution *next_best = NULL;

  for (int i = 0; i < n_particles_; i++) {
    double f = particles_[i]->move(bs);
    if (f < bf) {

      if (next_best) {
        delete next_best;
      }
      bf = f;
      next_best = particles_[i]->current_position()->clone();
    }
  }
  return next_best ? next_best : sol;
}
template <typename T> meta::ASolution *PSO<T>::run() {
  meta::ASolution *best = startSolution_->clone();
  for (int i = 0; i < tmax_; i++) {
    meta::ASolution *next = step(best);
    if (next != best) {
      delete best;
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

template class pso::Particle<meta::RnSolution>;
template class pso::Particle<meta::MyRnSolution>;
template class pso::PSO<meta::RnSolution>;
template class pso::PSO<meta::MyRnSolution>;
