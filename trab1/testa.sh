#!/bin/bash

const=0.0.03125
for k in {1..201};
do
  i=$k*$const
  echo "$i"
  ./a.out cara.obj rotatax/cara$k.ppm 1000 1000 500 500 600 $i 0 0 4 1 1 1
done


for k in {1..201};
do
  i=$k*$const
  ./a.out cara.obj rotatay/cara$k.ppm 1000 1000 500 500 600 0 $i 0 4 1 1 1
done


for k in {1..201};
do
  i=$k*$const
  ./a.out cara.obj rotataz/cara$k.ppm 1000 1000 500 500 600 0 0 $i 4 1 1 1
done


for k in {1..201};
do
  i=$k*$const
  ./a.out cara.obj rotataxyz/cara$k.ppm 1000 1000 500 500 600 $i $i $i 4 1 1 1
done
