#ifndef HISTO_H
#define HISTO_H

#include <vector> 

namespace hh{
  
std::vector<double> * histo(std::vector<int> xs, int bins=10,bool normed=false);
int pippo();

};
#endif

