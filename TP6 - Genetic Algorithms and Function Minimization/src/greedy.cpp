#include "greedy.hpp"

using namespace greedy;

Greedy::Greedy(meta::ASolution *start) : meta::AMeta(start, "Greedy") {
  index_ = 1;
}

void Greedy::reset(meta::ASolution *startSol) {
  meta::AMeta::reset(startSol);
  index_ = 1;
}

meta::ASolution *Greedy::step(meta::ASolution *sol) {

  meta::ASolution *next = NULL;
  meta::ASolution *ds = sol->sub_solution(index_, index_ + 1);
  double best_delta = ds->fitness();
  delete ds;
  iters_++;
  for (int i = index_ + 2; i < sol->n(); i++) {
    iters_++;
    ds = sol->sub_solution(index_, i);
    double delta = ds->fitness();
    delete ds;
    if (delta < best_delta) {
      meta::ASolution *s = sol->neighbour(index_ + 1, i);
      if (next) {
        delete next;
      }
      best_delta = delta;
      next = s;
    }
  }
  index_++;
  return next;
}

meta::ASolution *Greedy::run() {
  index_ = 0;
  // double fitness = startSolution_->fitness();
  meta::ASolution *sol = startSolution_->clone();
  while (true) {
    meta::ASolution *next = step(sol);
    if (index_ >= sol->n() - 1) {
      return sol;
    } else if (next) {
      delete sol;
      sol = next;
    }
  }
  return sol;
}
