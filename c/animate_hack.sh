#!/bin/sh
num=`printf "%0.4f" $1`
<<<<<<< HEAD
=======

if [ -e $num.png ]; then
  echo "$num.png exists..."
  exit
fi

>>>>>>> f7d391ffd4e3a29dbfab2a6347a0a4255c358a09
./ex2 5760 3240 10000000 -1.5625 -2 1.5625 2 10 10 $num | convert - -resize 1920x $num.png

