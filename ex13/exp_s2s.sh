#!/bin/sh
for((i=10000; i <= 100000; i+=10000)); do
    ./ex13 name output/Sorted$i.txt dummy/dummy$i.txt
done