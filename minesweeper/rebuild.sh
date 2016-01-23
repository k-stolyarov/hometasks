#!/bin/sh

OUTPUT=minesweeper
#CC_ARGS="--std=c++11"
CC_ARGS=""
LINK_ARGS="-lstdc++ -lcurses"
rm -f $OUTPUT
rm -rf *.o
gcc $CC_ARGS -c *.cpp
gcc -o $OUTPUT *.o $LINK_ARGS
