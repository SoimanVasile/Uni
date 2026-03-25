#!/bin/bash

if [ -z $1 ]; then
    echo "I need an input file"
    exit 1
fi

while read user; do
    
    if  pinky "$user" 2>/dev/null | grep -q "Name:" ; then
    result="${result} ${user}@scs.ubbcluj.ro,"
    fi

done < "$1"

echo "$result" | sed -E 's/,$//'



 
