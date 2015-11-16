#!/bin/bash
a=`echo "4*a(1.0)" | bc -l` ; echo ${a} # ← π を計算している。
b=`echo "c($a)" | bc -l` ; echo ${b} # ← cos(π)を計算している。
