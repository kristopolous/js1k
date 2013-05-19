#!/bin/sh
num=`printf "%0.4f" $1`
./ex2 5760 3240 10000000 -1.5625 -2 1.5625 2 10 10 $num | convert - -resize 1920x $num.png

