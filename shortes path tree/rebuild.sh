#!/bin/sh

OUTPUT=shortest_path_tree

rm -f $OUTPUT
rm -rf *.o
gcc -c *.c
gcc -o $OUTPUT *.o -lX11 -lm 
