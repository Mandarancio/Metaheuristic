#include "histo.h"
#include <algorithm>    // std::min_element, std::max_element


std::vector<double> * hh::histo(std::vector<int> xs, int bins,bool normed){
  std::vector<double> * res=new std::vector<double>[2];
  
  int min = *std::min_element(xs.begin(),xs.end());
  int max= *std::max_element(xs.begin(),xs.end());
  int histo_size = max-min;
  if (histo_size==0){
    histo_size=2;
    //min-=0;
   // max+;
  }
  if (histo_size<bins){
    bins=histo_size;
  }
  double norm_f = normed? 1.0/(double)xs.size():1.0; 
  double bin_size = histo_size/(double)bins;
  res[0].push_back(min-0.5*bin_size);
  res[1].push_back(0);
  
  for (int i = 0 ;i<bins;i++){
    res[0].push_back(min+i*bin_size-0.5*bin_size);
    res[0].push_back(min+(i+1)*bin_size-0.5*bin_size);
    res[1].push_back(0);
    res[1].push_back(0);
  }
  res[0].push_back(max+0.5*bin_size);
  res[1].push_back(0);
  for (int i =0;i<xs.size();i++){
    int v=xs[i];
    for (int j=1;j<1+bins*2;j+=2){
      if (v>=res[0][j] && v<(res[0][j+1])){
        res[1][j]+=1*norm_f;
        res[1][j+1]+=1*norm_f;
      }
    }
  }
  return res;
}

int hh::pippo(){
  return -1;
}
