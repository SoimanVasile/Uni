#!/bin/bash

if [[ -z $1 ]]; then
    echo "I need input file"
    exit 1
fi

D=$1

cat "$D" | tail -n +2 | while read mount; do
    if [[ -z "$mount" ]]; then
        continue
    fi
    mem=$(echo "$mount" | awk -F' ' '{print $2}' | sed -E 's/M//g')
    usage=$(echo "$mount" | awk '{print $5}' | sed -E 's/%//g')
    if (( $mem <= 1024 || $usage >= 80 )); then
        file_path=$(echo "$mount" | awk '{print $6}')
        echo "$file_path"
    fi
done
