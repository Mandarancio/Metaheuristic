#!/bin/sh

cd src/
# g++ main_matrix.cpp matrix.cpp exmath.cpp -O2 -std=c++11 -o ../bin/test
g++ test.cpp matrix.cpp exmath.cpp nn.cpp img_loader.cpp -O2 -std=c++11 -o ../bin/test
# g++ main_NN.cpp matrix.cpp exmath.cpp nn.cpp img_loader.cpp -O2 -std=c++11 -o ../bin/NN_test
# g++ main_img.cpp matrix.cpp img_loader.cpp -O2 -std=c++11 -o ../bin/img_test -lpython2.7
