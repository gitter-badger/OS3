#!/bin/bash
x=0
while [ ${x} -le 10 ]
do
	v=`echo "${x} * 0.31416" | bc -l`
	echo "sin(${v}) = " `echo "s(${v})" | bc -l`.
	x=`expr ${x} + 1`
done 
