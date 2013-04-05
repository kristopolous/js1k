#!/bin/sh
num=`printf "%0.4f" $1`
./ex2 4800 4800 1000000 -3 -3 3 3 10 5 $num | convert - -resize 1200x $num.png

