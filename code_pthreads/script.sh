#!/bin/bash
echo " " > pthreasults.txt
for i in {16..24}
do
  for j in {1..8}
  do
    qsort $i $j >> pthreasults.txt
  done
done
