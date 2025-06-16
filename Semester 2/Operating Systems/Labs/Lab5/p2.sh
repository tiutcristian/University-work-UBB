#!/bin/bash

# NU I BINE

find "$1" -type f | while read f; do
    if grep -q "[0-9]{5,}"; then
        echo "$f"
    fi
done
