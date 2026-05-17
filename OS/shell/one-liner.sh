#!/bin/bash

[[ $#  -eq 3 && -f "$1" ]] || exit 1; awk -v f1=$2 -v f2=$3 'BEGIN {c1=0; c2=0;} /^[A-Z]/ {print > f1; c1++} /\?$/ { print > f2; c2++} END{print "Linii care incep cu litera mare: " c1; print "Linii care se termina cu ?: " c2}' "$1"

