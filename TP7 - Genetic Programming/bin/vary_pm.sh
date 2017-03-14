#! /bin/bash
echoerr() { printf "%s\n" "$*" >&2; }

./gp -header
for pm in `LANG=en_US seq 0.0 0.1 1.0`;
do
  echoerr 'PM: ' $pm
  ./gp -csv -plength 13 -pop 30 -pm $pm -pc 0.6
done

exit 0
