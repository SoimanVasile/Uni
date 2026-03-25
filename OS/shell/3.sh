#!/bin/bash

if [[ -z $1 ]]; then
    echo "No input file"
    exit 1
fi

D=$1

$(touch test.txt)
find $D | grep -E ".\.log" | while read file_path; do
    $(sort "$file_path" > test.txt)
    mv test.txt "$file_path"
done
