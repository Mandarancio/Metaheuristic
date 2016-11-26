#!/bin/sh

cd src/
# g++ stepper.cpp pso.cpp display.cpp exmath.cpp meta.cpp matrix.cpp rsolution.cpp -O3 -std=c++11 -o ../bin/steps -lpython2.7 -g
# g++ run_once.cpp pso.cpp display.cpp exmath.cpp meta.cpp matrix.cpp rsolution.cpp -O3 -std=c++11 -o ../bin/simple_pso -lpython2.7 -g
g++ pso_nn.cpp pso.cpp display.cpp exmath.cpp meta.cpp nn.cpp mynn.cpp img_loader.cpp matrix.cpp rsolution.cpp -O3 -std=c++11 -o ../bin/pso_nn 
