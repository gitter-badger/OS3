#!/bin/bash
# Greeting Script
g='Hello'
d=`date +%d`
dm=`expr $d - 1`
t=`date +%H`
m=`date +%M`
d2min () {
	min=`echo "(($1 * 24) + $2) * 60 + $3" | bc -l`
}
d2min ${dm} ${t} ${m}
echo ${g}, "about $min minutes have passed this month." 
