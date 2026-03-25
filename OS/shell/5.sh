#!/bin/bash

while true; do
    
    for program in $@; do
        pid=$(ps -a | grep "$program" | awk -F' ' '{print $1}')
        if [[ -n $pid ]]; then
            kill "$pid"
            echo "killed $program"
        fi
    done

    sleep 1
done
