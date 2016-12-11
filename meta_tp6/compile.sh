#!/bin/sh

cd src/
g++ main.cpp geneticalg.cpp -o ../bin/test -g
# g++ stepper.cpp pso.cpp display.cpp exmath.cpp meta.cpp matrix.cpp rsolution.cpp nn.cpp mynn.cpp img_loader.cpp -O3 -std=c++11 -o ../bin/steps -lpython2.7
# echo "steps: Done";
# g++ run_once.cpp pso.cpp display.cpp exmath.cpp meta.cpp matrix.cpp rsolution.cpp nn.cpp mynn.cpp img_loader.cpp -O3 -std=c++11 -o ../bin/simple_pso -lpython2.7
# echo "simple_pso: Done";
# g++ pso_nn.cpp pso.cpp display.cpp exmath.cpp meta.cpp nn.cpp mynn.cpp img_loader.cpp matrix.cpp rsolution.cpp -O3 -std=c++11  -o ../bin/pso
# echo "pso: Done";
# g++ landscape.cpp display.cpp exmath.cpp meta.cpp nn.cpp mynn.cpp img_loader.cpp matrix.cpp rsolution.cpp -O3 -std=c++11  -o ../bin/landscape  -lpython2.7
# echo "landscape: Done";
# g++ stepper_nn.cpp pso.cpp display.cpp exmath.cpp meta.cpp nn.cpp mynn.cpp img_loader.cpp matrix.cpp rsolution.cpp -O3 -std=c++11  -o ../bin/steps_nn -lpython2.7
# echo "steps_nn: Done";
