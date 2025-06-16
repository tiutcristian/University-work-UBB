#!/bin/bash

export sum=0

export cnt=0

find "$1" -type f | ( while read f; do

    if file "$f" | grep -q "ASCII text"; then

        c=`cat "$f"|wc -l`

        sum=$(($sum+$c))

        cnt=$(($cnt+1))

    fi

done

echo "sum: $sum; cnt: $cnt; avg: $(($sum/$cnt))" )
