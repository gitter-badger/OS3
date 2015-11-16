#!/bin/bash
fn=~/.bashrc
if [ -e ${fn} ]
then
	cat ${fn}
else
	echo "You has no ${fn}."
fi 
