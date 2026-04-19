#!/bin/bash

cat who.fake | awk '{print $1}' | while read name; do
    echo "$name $(cat ps.fake | grep -E "^$name" | wc -l)"

done
