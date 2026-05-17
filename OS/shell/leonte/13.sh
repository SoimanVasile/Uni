#!/bin/bash


while read name; do
    if [[ -z "$name" ]]; then
        echo "Se inchide programu"
        break;
    fi

    if [[ -n $(cat /etc/passwd | awk -F':' '{print $1}' | grep -E "^$name$") ]]; then
        count=$(ps -u --all | tail -n +2 | grep -E "^$name " -c)
        echo "$name are $count procese"
    fi
done
