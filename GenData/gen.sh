#!/bin/bash
echo GenData
for((i=10000; i <= 100000; i+=10000)); do
    echo $i
    ./GenData $i ListData$i.txt
    ./GenData -n $i ArrayData$i.txt
done

mkdir ListData ArrayData

for((i=10000; i <= 100000; i+=10000)); do
    mv ListData$i.txt ListData/
    mv ArrayData$i.txt ArrayData/
done