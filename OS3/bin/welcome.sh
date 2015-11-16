#!/bin/bash
# Welcome Script
uid=`whoami`
g="$1 says \"Thank you, $uid and $2\""
echo ${g}
shift
g="$1 says \"Thank you, $uid and $2\""
echo ${g} 
