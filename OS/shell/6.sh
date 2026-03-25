#!/bin/bash

if [ -z $1 ]; then
    echo "i need an input file"
    exit 1
fi

D=$1

find "$D" -type f -perm -o=w | while read file_path; do
    
    echo "before: $(ls -l "$file_path")"
    chmod o-w "$file_path"
    echo "after: $(ls -l "$file_path")"
done
