#!/bin/bash

d="array-notations reducers"

for dir in $d
do
  cd $dir
  rm -rf *.o
  cd ..
done

