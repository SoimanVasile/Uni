#!/bin/bash

if [[ -z $1 ]]; then
    echo "No input file!"
    exit 1
fi

find "$1" -type f -name "*.log" | while read file_path; do
    cat "$file_path" | sort > temp
    rm "$file_path"
    mv temp "$file_path"
done
