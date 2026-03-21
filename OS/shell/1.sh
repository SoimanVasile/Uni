#!/bin/bash

if [[ -z $1 ]]; then
    echo "Didnt give an input file!"
    exit 1
fi

D=$1
cat "$D" | awk -F' ' 'NF > 0  {print $1}' | sort | uniq | while read -r name; do

    count=$(grep -c -E "^$name" ./ps.fake)
    echo "$name: $count"

done
