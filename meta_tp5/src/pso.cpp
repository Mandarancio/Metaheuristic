#include "pso.hpp"
#include "exmath.hpp"
#include <iostream>
using namespace pso;

Particle::Particle(meta::RnSolution * position,double omega, double c1, double c2,double vmax):
position_(position),speed_(position->n()), omega_(omega), c1_(c1), c2_(c2),vmax_(vmax)
{
  particle_best_ = dynamic_cast<meta::RnSolution*>(position->clone());
  for (int i=0 ;i<position->n();i++){
    speed_.set(math::r()*2*vmax-vmax,i);
  }
}

Particle::~Particle()
{
  delete position_;
  if (particle_best_)
  {
    delete particle_best_;
  }
}

math::Vector<double> Particle::speed()
{
  return speed_;
}

double Particle::current_fitness()
{
  return position_->fitness();
}

meta::RnSolution * Particle::current_position()
{
  return position_;
}

double Particle::best_fitness()
{
  return particle_best_->fitness();
}

meta::RnSolution * Particle::best_position()
{
  return particle_best_;
}

math::Vector<double> Particle::bounce(math::Vector<double> p)
{
  // double b_factor = 0.9;
  math::Vector<double> M=position_->max();
  math::Vector<double> m=position_->min();
  int n = position_->n();
  //bool unchanged = true;
  for (int i=0;i<n;i++)
  {
    double v = p.at(i);
    if (v<m.at(i))
    {
      v=m.at(i);
      speed_.set(-speed_.at(i),i);
      //unchanged = false;
    }
    else if (v>M.at(i))
    {
      v= M.at(i);//-b_factor*v;
      //unchanged = false;
      speed_.set(-speed_.at(i),i);
    }
    p.set(v,i);
  }
  return p;
}

math::Vector<double> Particle::limit(math::Vector<double> s)
{
  for (unsigned int i = 0;i<s.columns();i++)
  {
    if (s.at(i)<-vmax_)
    {
      s.set(-vmax_,i);
    }
    else if (s.at(i)>vmax_)
    {
      s.set(vmax_,i);
    }
  }
  return s;
}


double Particle::move(meta::RnSolution * group_best)
{
  double r1= math::r();
  double r2= math::r();

  math::Vector<double> p = position_->solution();
  math::Vector<double> bt = particle_best_->solution()-p;
  math::Vector<double> bg = group_best->solution()-p;

  // std::cout<<bt.toString()<<"\n"<<std::cout<<p.toString()<<"\n";
  // std::cout<<speed_.toString()<<std::endl;
  // std::cout<<(speed_*omega_+ bt*r1*c1_+bg*r2*c2_).toString()<<std::endl;
  speed_ = (speed_*omega_+ bt*r1*c1_+bg*r2*c2_);
  // std::cout<<speed_.toString()<<std::endl;
  p = bounce(p+speed_);

  meta::RnSolution * x= position_->create(p);
  delete position_;

  double f = x->fitness();
  if (f>particle_best_->fitness())
  {
    delete particle_best_;
    particle_best_ = dynamic_cast<meta::RnSolution*>(x->clone());
  }
  position_ = x;
  return f;
}

PSO::PSO(meta::RnSolution * startSolution, int n_particle, int tmax, double omega, double c1, double c2, double vmax):
meta::AMeta(startSolution,"PSO"), omega_(omega),c1_(c1),c2_(c2),vmax_(vmax),n_particles_(n_particle),tmax_(tmax)
{
  for (int i =0;i<n_particle;i++)
  {
    Particle * p = new Particle(dynamic_cast<meta::RnSolution*>(startSolution->random()), omega, c1,c2,vmax);
    particles_.push_back(p);
  }
}

PSO::~PSO()
{
  for (int i=0;i<n_particles_;i++)
  {
    delete particles_[i];
  }
}

meta::ASolution * PSO::step(meta::ASolution * sol)
{
  double bf = sol->fitness();
  meta::RnSolution *bs = dynamic_cast<meta::RnSolution*>(sol);
  meta::ASolution * next_best = NULL;

  for (int i=0;i<n_particles_;i++)
  {
    double f = particles_[i]->move(bs);
    if (f>bf){
      if (next_best)
      {
        delete next_best;
      }
      bf =f;
      next_best = particles_[i]->current_position()->clone();
    }
  }
  return next_best ? next_best : sol;
}

meta::ASolution * PSO::run()
{
  meta::ASolution * best = startSolution_->clone();
  for (int i =0;i<tmax_;i++)
  {
    meta::ASolution * next = step(best);
    if (next!=best)
    {
      delete best;
      best = next;
    }
  }
  return best;
}

void PSO::reset(meta::ASolution * sol)
{
  meta::AMeta::reset(sol);
  for (int i =0;i<n_particles_;i++)
  {
    delete particles_[i];
    particles_[i]= new Particle(dynamic_cast<meta::RnSolution*>(sol->random()), omega_, c1_,c2_, vmax_);
  }
}

std::vector<Particle*> PSO::particles()
{
  return particles_;
}
