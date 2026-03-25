#!/bin/bash

if [ -z $1 ]; then
    echo "I need an input file"
    exit 1
fi

D=$1

find "$D" | while read file_path; do
    
    if [ -L "$file_path" ]; then
        
        if [ ! -e "$file_path" ]; then
            echo "$file_path"
        fi

    fi
done
