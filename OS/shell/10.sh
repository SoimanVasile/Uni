#!/bin/bash

first_day=$(date +%Y-%m-01)

last -s "$first_day" | awk '{print $1}' | sort | uniq | while read user; do
    if [[ -z "$user" ]]; then
        continue
    fi
    echo "$user: $(last -s "$first_day"| grep -Ec "^$user")"
done
