#!/bin/bash
for x in 0 1 2 3 4 5 6 7 8 9 10
do
	v=`echo "${x} * 0.31416" | bc -l`
	echo "sin(${v}) = " `echo "s(${v})" | bc -l`.
done 
