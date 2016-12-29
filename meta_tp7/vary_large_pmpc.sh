#! /bin/bash
echoerr() { printf "%s\n" "$*" >&2; }

./gp -header
for pm in `LANG=en_US seq 0.1 0.1 0.7`;
do
  echoerr 'PM: ' $pm
  for pc in `LANG=en_US seq 0.1 0.1 0.7`;
  do
    echoerr ' PC: ' $pc
    ./gp -csv -plength 13 -pop 30 -pm $pm -pc $pc 
  done
done

exit 0
