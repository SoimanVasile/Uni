#!/bin/bash

if [[ -z $1 ]]; then
    echo "No input file!"
    exit 1
fi

D=$1
freq=0
find "$D" | grep -E ".\.c" | while read file_path; do
    word_count=$(wc "$file_path" | awk -F' ' '{print $1}')
    if (( $word_count >= 500 && freq < 2 )); then
        echo "$file_path"
        freq=$((freq + 1))
    fi
done
