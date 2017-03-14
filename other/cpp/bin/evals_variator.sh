#! /bin/bash
# testing 640,000 different possibilities
# varing tmax, n particles, omega, c1, c2 and max speed
# omega

# for j in `seq 10 1 20`;
# do
# for i in `seq 1 1 50`;
# do
#   ./ga -bit 16 -evals $j -pm 0.1 -pc 0.6 -pop 100
# done
#
# done
for j in `seq 10 10 100`;
do

    ./ga -bit 16 -evals $j -pm 0.1 -pc 0.6 -pop 100 -it 50

done

for j in `seq 150 50 1000`;
do
    ./ga -bit 16 -evals $j -pm 0.1 -pc 0.6 -pop 100 -it 50
done
exit 0
