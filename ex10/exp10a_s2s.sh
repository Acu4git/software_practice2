#!/bin/bash
for((i=10000; i <= 100000; i+=10000)); do
    ./ex10a name output_10a/Sorted$i.txt dummy/dummy_array_$i.txt
done