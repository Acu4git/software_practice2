#!/bin/bash
for((i=10000; i <= 100000; i+=10000)); do
    ./ex10 name input/ListData$i.txt output/Sorted$i.txt
done