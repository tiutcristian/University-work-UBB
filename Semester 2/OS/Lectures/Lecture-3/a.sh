#!/bin/bash

A=7
B=9
expr 7+9
expr $A+$B

echo $*
echo $@
echo $#
echo $0 $1 $2 $3 $9
shift 2
echo $*
echo $@
echo $0 $1 $2 $3 $9
echo $#
