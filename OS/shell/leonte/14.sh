#!/bin/bash

if [[ -z $2 ]]; then
    echo "no input file!"
    exit 1
fi
count=0
cat "$1" | while read line; do
    
    if [[ -z $(grep -E "$line" $2) ]]; then
        echo "$line"
        count=$( expr count+1)
    fi

done

echo "Numarul de linii este egal cu $count"
