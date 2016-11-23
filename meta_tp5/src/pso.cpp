#include "pso.hpp"
#include "exmath.hpp"

using namespace pso;

Particle::Particle(meta::RnSolution * position,double omega, double c1, double c2,double vmax):
position_(position), omega_(omega), c1_(c1), c2_(c2), vmax_(vmax)
{
  particle_best_ = dynamic_cast<meta::RnSolution*>(position->clone());
  speed_=std::vector<double>();
  for (int i=0;i<position->n();i++){
    speed_.push_back(math::r()*2*vmax-vmax);
  }
}

Particle::~Particle()
{
  delete position_;
  if (particle_best_)
  {
    delete particle_best_;
  }
  speed_.clear();
}

std::vector<double> Particle::speed()
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

std::vector<double> Particle::bounce(std::vector<double> p)
{
  double b_factor = 0.9;
  std::vector<double> M=position_->max();
  std::vector<double> m=position_->min();
  int n = position_->n();
  //bool unchanged = true;
  for (int i=0;i<n;i++)
  {
    double v = p[i];
    if (v<m[i])
    {
      v=m[i];
      speed_[i]=-speed_[i];
      //unchanged = false;
    }
    else if (v>M[i])
    {
      v=M[i];//-b_factor*v;
      //unchanged = false;
      speed_[i]=-speed_[i];
    }
    p[i]=v;
  }
  return p;
}

std::vector<double> Particle::limit(std::vector<double> s)
{
  for (unsigned int i = 0;i<s.size();i++)
  {
    if (s[i]<-vmax_)
    {
      s[i]=-vmax_;
    }
    else if (s[i]>vmax_)
    {
      s[i]=vmax_;
    }
  }
  return s;
}


double Particle::move(meta::RnSolution * group_best)
{
  double r1= math::r();
  double r2= math::r();
  
  std::vector<double> p = position_->solution();
  std::vector<double> bt = math::sub(particle_best_->solution(),p);
  std::vector<double> bg = math::sub(group_best->solution(),p);
  speed_= limit(math::sum(math::sum(math::mul(omega_,speed_),math::mul(r1*c1_,bt)),math::mul(r2*c2_,bg)));
  p = bounce(math::sum(p,speed_));
  
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

PSO::PSO(meta::RnSolution * startSolution, int n_particle, int tmax, double omega, double c1, double c2, double vmax)
: n_particles_(n_particle), tmax_(tmax),omega_(omega),c1_(c1),c2_(c2),vmax_(vmax), meta::AMeta(startSolution,"PSO")
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
