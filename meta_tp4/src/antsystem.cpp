#include "antsystem.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>


using namespace as;

GroupKnowledge::GroupKnowledge(meta::ASolution * baseSolution, double t0, double alpha, double beta, double q,double evap):
  baseSolution_(baseSolution),t0_(t0), beta_(beta), alpha_(alpha), q_(q), evap_(evap)
{
  n_=baseSolution->n();
  delta_ph = new double*[n_];
  pherormones = new double*[n_];
  visibility = new double*[n_];
  ids = new int[n_];
  for (int i = 0; i< n_; i++)
  {
    delta_ph[i]=new double[n_];
    pherormones[i] = new double[n_];
    visibility[i] = new double[n_];
    ids[i]=i;
  }
  for (int i = 0; i < n_; i++)
  {   
    for (int j = i; j < n_; j++)
    { 
      setPherormones(t0,i,j);
      computeVisibility(i,j);
      setDelta(0,i,j);
    }
  }
}

void GroupKnowledge::updateDelta(double delta, int a, int b){
  delta_ph[a][b]+=delta;
  delta_ph[b][a]+=delta;  
}

void GroupKnowledge::setDelta(double delta, int a, int b)
{
  delta_ph[a][b]=delta;
  delta_ph[b][a]=delta;
}

void GroupKnowledge::updatePh()
{
  for (int i = 0; i < n_-1; i++)
  {
    for (int j = i+1; j < n_; j++)
    {     
      double p = pherormones[i][j];
      p = (1.-evap_)*p+delta_ph[i][j];
      pherormones[j][i]=p;
      pherormones[i][j]=p;
    }
  }
}

void GroupKnowledge::resetDeltas()
{
  for (int i = 0; i < n_; i++)
  {
    for (int j = i; j < n_; j++)
    {     
      setDelta(0,i,j);
    }
  }
}   

double GroupKnowledge::q()
{
  return q_;
}

double GroupKnowledge::alpha()
{
  return alpha_;
}

double GroupKnowledge::beta()
{
  return beta_;
}

int GroupKnowledge::n()
{
  return n_;
}



void GroupKnowledge::computeVisibility(int i, int j)
{
  double d =baseSolution_->sub_fitness(i,j);
 
  visibility[i][j]=1./d;
  visibility[j][i]=1./d;
}


void GroupKnowledge::setPherormones(double ph,int a, int b)
{
  pherormones[a][b]=ph;
  pherormones[b][a]=ph;
}



meta::ASolution * GroupKnowledge::fromItinerary(int* itinerary)
{
  std::vector<int> it(itinerary,itinerary+n_);
  return  baseSolution_->create(it);
}


Ant::Ant(int id,GroupKnowledge * gk):
  id_(id), gk_(gk), length_(0), J(NULL), visitedcity_(NULL)
{
  n_=gk->n();
}

bool Ant::notInJ(int i)
{
  return !J[i];
}

double Ant::p(int i , int j)
{
  if (notInJ(j)){
    return 0;
  }
  double num = pow(gk_->pherormones[i][j],gk_->alpha())*pow(gk_->visibility[i][j],gk_->beta());
  double den = 0;
  for (int k = 0;k<n_;k++)
  {
    if (J[k]){
      int l = k;
      den+=pow(gk_->pherormones[i][l],gk_->alpha())*pow(gk_->visibility[i][l],gk_->beta());
    }
  }
  return num/den;
}

int Ant::chooseNext(int a)
{
  double p_c = 0;
  double r = double(rand())/RAND_MAX;
  for (int i = 0 ;i<n_;i++)
  {
    if (J[i])
    {
      int b = i;
      double pcb= p(a,b);
      if (r>=p_c && r<p_c+pcb){
        return b;
      }
      p_c+=pcb;
    }
  }
  return -1;
}

int*  Ant::walk(int start_id){
  if (visitedcity_!=NULL){
    delete[] visitedcity_;
    delete[] J;
  }
  visitedcity_ = new int[n_];
  J = new int[n_];
  visitedcity_[0]=start_id;
  for (int i = 0 ;i<n_;i++)
  {
    J[i]=1;
  }
  J[start_id]=0;
  int a = start_id;
  double l = 0;
  for (int i=1;i<n_;i++)
  {
    int b = chooseNext(a);
    visitedcity_[i]=b;
    J[b]=0;
    l+= 1/gk_->visibility[a][b];
    a=b;
  }  
  int b= visitedcity_[0];
  l+= 1./gk_->visibility[a][b];
  length_=l;
  return visitedcity_;
}


double Ant::L()
{
  return length_;
}

AntSystem::AntSystem(meta::ASolution * startSolution, GroupKnowledge * gk,int n_ants,int max_t):
  meta::AMeta(startSolution,"Ant System"), gk_(gk), max_t_(max_t)
{
  n_ants_= n_ants>0?n_ants:gk->n();
  for (int i=0;i<n_ants_;i++){
    ants_.push_back(Ant(i,gk_));
  }  
}

void Ant::updateDelta()
{
  double delta= gk_->q()/length_;
  int a=visitedcity_[0];
  for (int i=1;i<n_;i++)
  {
    int b = visitedcity_[i];
    gk_->updateDelta(delta,a,b);
    a = visitedcity_[i];
  }
  gk_->updateDelta(delta,a,visitedcity_[0]);
}

meta::ASolution * AntSystem::step(meta::ASolution * sol)
{
  int n_ = gk_->n();
  int* m_path;
  int * path = ants_[0].walk(0);
  m_path = path;
  //memcpy(m_path,path,n_*sizeof(int));
  double min=ants_[0].L(); 
  bool rand_start=n_ants_==gk_->n(); 
  for (int i = 1;i<n_ants_; i++)
  {
    int s=rand_start?i:rand()%n_;
    path= ants_[i].walk(s);
    double l = ants_[i].L();
    if (l<min){
      min=l;
      m_path= path;
    }
  }
  gk_->resetDeltas();
  for (int i = 0;i<n_ants_;i++)
  {
    ants_[i].updateDelta();
  }
  gk_->updatePh();
  if (min<sol->fitness()){
    delete sol;
    return gk_->fromItinerary(m_path);
  }
  return sol;
}

meta::ASolution * AntSystem::run()
{
  meta::ASolution * s = startSolution_->clone();
  for (int i = 0;i<max_t_;i++)
  {
    s = step(s);
  }
  return s;
}


