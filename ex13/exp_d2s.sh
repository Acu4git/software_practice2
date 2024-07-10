#!/bin/sh
for((i=10000; i <= 100000; i+=10000)); do
    ./ex13 name input/ListData$i.txt output/Sorted$i.txt
done