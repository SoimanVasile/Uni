#!/bin/bash

for A in  $*; do
  if test -d $A; then
    echo $A e director
  elif test -f $A; then
    echo $A e fisier
  elif echo $A | grep -E -q "^[0-9]+$";then
    echo $A e numar
  else 
    echo $A e altceva
  fi
done

while read B; do
  echo am citit $B
done
