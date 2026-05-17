#!/bin/bash

N=0
for F in *.c; do
    K=$(grep -E -v "^[ {}]*$" "$F" | wc -l)
    N=$(($N + $K))
done

echo $N
