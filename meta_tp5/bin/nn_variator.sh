#! /bin/bash
# testing 640,000 different possibilities
# varing tmax, n particles, omega, c1, c2 and max speed
# omega
for i in `LC_NUMERIC="en_US.UTF-8" seq 0.1 0.1 1.0`;
do
  # c1
  for j in `LC_NUMERIC="en_US.UTF-8" seq 0.1 0.1 2.0`;
  do
    # c2
    for h in `LC_NUMERIC="en_US.UTF-8" seq 0.1 0.1 2.0`;
    do
      # vmax
      for v in `LC_NUMERIC="en_US.UTF-8" seq 0.1 0.1 1.0`;
      do
        # tmax
        for t in `seq 10 5 30`;
        do
          # npart
          for p in `seq 15 10 55`;
          do
            ./pso_nn -csv -tmax $t -npart $p -omega $i -c1 $j -c2 $h -vmax $v
          done
        done
      done
    done
  done
done

exit 0
