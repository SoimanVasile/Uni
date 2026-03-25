#!/bin/bash

if [ -z $1 ]; then
    echo "i need an input file"
    exit 1
fi

find "$1" -type f | while read file_path; do
    
    md5sum "$file_path"

done > test_file

awk '{print $1}' test_file | sort | uniq -d
