#!/bin/bash

if [[ -z $1 ]]; then
    echo "No input file!"
    exit 1
fi

find "$1" -type l | while read file_path; do
    if [[ -h "$file_path" ]]; then
        if [[ ! -e "$file_path" ]]; then
            echo "Broken link: $file_path"
        fi
    fi
done
