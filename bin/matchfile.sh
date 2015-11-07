#!/bin/bash
echo -n "Please input file name: "
read fn
case ${fn} in
	*.txt )
		echo "${fn} is text file.";;
	*.c )
		echo "${fn} is C program file.";;
	* )
		echo "Hey, what is ${fn} ? You know it?";;
esac 
