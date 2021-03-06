#! /bin/bash
# testing 640,000 different possibilities
# varing tmax, n particles, omega, c1, c2 and max speed
# omega
for j in `LC_NUMERIC="en_US.UTF-8" seq 0.0 0.05 0.6`;
do

    ./ga -bit 16 -evals 10 -pm 0.1 -pc $j -pop 100 -it 50

done

exit 0
