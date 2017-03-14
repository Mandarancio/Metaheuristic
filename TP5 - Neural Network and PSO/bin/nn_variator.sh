#! /bin/bash
# testing 640,000 different possibilities
# varing tmax, n particles, omega, c1, c2 and max speed
# omega
for i in `LC_NUMERIC="en_US.UTF-8" seq 5 5 50`;
do
  for j in `seq 1 1 5`;
  do
    ./pso -csv -tmax $i -npart 25 -omega 0.8 -c1 1.8 -c2 1.5 -vmax 0.5
  done
done

for i in `LC_NUMERIC="en_US.UTF-8" seq 5 5 50`;
do
  for j in `seq 1 1 5`;
  do
    ./pso -csv -tmax 25 -npart $i -omega 0.8 -c1 1.8 -c2 1.5 -vmax 0.5
  done
done

for i in `LC_NUMERIC="en_US.UTF-8" seq 0.05 0.05 0.5`;
do
  for j in `seq 1 1 5`;
  do
    ./pso -csv -tmax 25 -npart 25 -omega 0.8 -c1 1.8 -c2 1.5 -vmax $i
  done
done

for i in `LC_NUMERIC="en_US.UTF-8" seq 0.5 0.05 0.9`;
do
  for j in `seq 1 1 5`;
  do
    ./pso -csv -tmax 25 -npart 25 -omega $i -c1 1.8 -c2 1.5 -vmax 0.5
  done
done
exit 0
