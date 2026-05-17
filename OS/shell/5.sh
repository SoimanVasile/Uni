#!/bin/bash

if [[ -z $1 ]]; then
    echo "No input file!"
    exit 1
fi

while true; do
    for name in $@; do
        pids=$(ps -all | tail -n +2 | grep "$name$" | awk '{print $4}')
        for pid in $pids; do
            kill "$pid"
            echo "Killed $name with pid: $pid"
        done
    done
done
