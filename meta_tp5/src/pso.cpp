#include "pso.hpp"
#include "exmath.hpp"
#include "mynn.hpp"
#include <iostream>
using namespace pso;

template <typename T>
Particle<T>::Particle(T *position, double omega, double c1, double c2,
                      double vmax)
    : position_(position), speed_(position->n()), omega_(omega), c1_(c1),
      c2_(c2), vmax_(vmax) {
  particle_best_ = dynamic_cast<T *>(position->clone());
  for (int i = 0; i < position->n(); i++) {
    speed_.set(math::r() * 2 * vmax - vmax, i);
  }
}

template <typename T> Particle<T>::~Particle() {
  delete position_;
  if (particle_best_) {
    delete particle_best_;
  }
}
template <typename T> math::Vector<double> Particle<T>::speed() {
  return speed_;
}

template <typename T> double Particle<T>::current_fitness() {
  return position_->fitness();
}

template <typename T> T *Particle<T>::current_position() { return position_; }

template <typename T> double Particle<T>::best_fitness() {
  return particle_best_->fitness();
}

template <typename T> T *Particle<T>::best_position() { return particle_best_; }

template <typename T>
math::Vector<double> Particle<T>::bounce(math::Vector<double> p) {
  // double b_factor = 0.9;
  math::Vector<double> M = position_->max();
  math::Vector<double> m = position_->min();
  int n = position_->n();
  // bool unchanged = true;
  for (int i = 0; i < n; i++) {
    double v = p.at(i);
    if (v < m.at(i)) {
      double x = 0.9 * (v - m.at(i));
      v = m.at(i) - x;
      if (v > M.at(i)) {
        v = M.at(i);
      }
      speed_.set(-speed_.at(i), i);
      // unchanged = false;
    } else if (v > M.at(i)) {
      double x = 0.9 * (v - M.at(i));
      v = M.at(i) - x; //-b_factor*v;
      if (v < m.at(i)) {
        v = m.at(i);
      }
      // unchanged = false;
      speed_.set(-0.9 * speed_.at(i), i);
    }
    p.set(v, i);
  }
  return p;
}

template <typename T>
math::Vector<double> Particle<T>::limit(math::Vector<double> s) {
  for (unsigned int i = 0; i < s.columns(); i++) {
    if (s.at(i) < -vmax_) {
      s.set(-vmax_, i);
    } else if (s.at(i) > vmax_) {
      s.set(vmax_, i);
    }
  }
  return s;
}

template <typename T> double Particle<T>::move(T *group_best) {
  double r1 = math::r();
  double r2 = math::r();

  math::Vector<double> p = position_->solution();
  math::Vector<double> bt = particle_best_->solution() - p;
  math::Vector<double> bg = group_best->solution() - p;

  // std::cout<<bt.toString()<<"\n"<<std::cout<<p.toString()<<"\n";
  // std::cout<<speed_.toString()<<std::endl;
  // std::cout<<(speed_*omega_+ bt*r1*c1_+bg*r2*c2_).toString()<<std::endl;
  // std::cout<<speed_.toString()<<std::endl;
  speed_ = (speed_ * omega_ + bt * r1 * c1_ + bg * r2 * c2_)+(math::r(speed_.size(),0.1)-0.05);
  p = bounce(p + speed_);
  T *x = dynamic_cast<T *>(position_->create(p));
  delete position_;

  double f = x->fitness();
  // std::cout<<f<<std::endl;
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
  // std::cout << "Fitness: " << bf << "\n";

  for (int i = 0; i < n_particles_; i++) {
    double f = particles_[i]->move(bs);
    if (f < bf) {
      // std::cout << "New Best: " << f << "\n";

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
  // std::cout << "Fitness: " << best->fitness() << "\n";
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
