#!/bin/bash
for((i=10000; i <= 100000; i+=10000)); do
    ./ex10a name input_10a/ArrayData$i.txt output_10a/Sorted$i.txt
done