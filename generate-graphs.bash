#!/bin/bash
mkdir -p graphs/png
for i in {1..6}; do
    python3 graphs/exhibit.py -i reports/$i.csv -t $i -r 5 -o "graphs/png/test$i.png"
done
