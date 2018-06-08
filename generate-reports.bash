#!/bin/bash
pushd build
for t in {1..6}; do
    ./polynneal 5 0.99997 1000 300000 csv ../reports/$t < ../test/test$t.txt > ../reports/$t.csv
done
popd
