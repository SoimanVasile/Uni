#!/bin/bash

if [[ -z $1 ]]; then
    echo "No input file!"
    exit 1
fi

freq=0
find "$1" -type f -name "*.c" | while read file_path; do
    number_of_lines=$(cat "$file_path" | wc -l)
    if (( number_of_lines >= 500 )); then
        echo "$file_path"
        ((freq++))
    fi

    if (( freq == 2)); then
        break
    fi
done
