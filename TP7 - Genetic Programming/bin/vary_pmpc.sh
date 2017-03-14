#! /bin/bash
echoerr() { printf "%s\n" "$*" >&2; }

./gp -header
for pm in `LANG=en_US seq 0.00 0.02 0.14`;
do
  echoerr 'PM: ' $pm
  for pc in `LANG=en_US seq 0.42 0.02 0.54`;
  do
    echoerr ' PC: ' $pc
    ./gp -csv -plength 13 -pop 30 -pm $pm -pc $pc
  done
done

exit 0
