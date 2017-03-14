#ifndef HISTO_H
#define HISTO_H

#include <algorithm>
#include <vector>

namespace hh {

template <typename Numeric>
std::vector<double> *histo(std::vector<Numeric> xs, unsigned int bins = 10) {
  std::vector<double> *res = new std::vector<double>[ 2 ];

  Numeric min = *std::min_element(xs.begin(), xs.end());
  Numeric max = *std::max_element(xs.begin(), xs.end());
  Numeric histo_size = max - min;
  /*if (histo_size==0){
    histo_size=2;
  }*/
  if (histo_size<bins){
    bins=histo_size+1;
  }

  double bin_size = histo_size / (double)bins;
  res[0].push_back(min - 0.5 * bin_size);
  res[1].push_back(0);

  for (unsigned int i = 0; i < bins; i++) {
    res[0].push_back(min + i * bin_size - 0.5 * bin_size);
    res[0].push_back(min + (i + 1) * bin_size - 0.5 * bin_size);
    res[1].push_back(0);
    res[1].push_back(0);
  }
  res[0].push_back(res[0][res[0].size() - 1]);
  res[1].push_back(0);

  for (unsigned int i = 0; i < xs.size(); i++) {
    Numeric v = xs[i];

    for (unsigned int j = 1; j < 1 + bins * 2; j += 2) {
      if (v >= res[0][j] && v < (res[0][j + 1])) {
        res[1][j] += 1;
        res[1][j + 1] += 1;
      }
    }
  }
  return res;
};


};
#endif
