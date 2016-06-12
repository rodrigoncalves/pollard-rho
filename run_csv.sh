#!/bin/bash
input="curves.csv"

while IFS=',' read -r f1 f2 f3 f4 f5 f6 f7 f8 f9
do
    time ./bin/pollardrho $f1 $f2 $f3 $f4 $f5 $f6 $f7 $f8 $f9
done < "$input"
