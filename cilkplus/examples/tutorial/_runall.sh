#!/bin/bash

d="array-notations reducers"

for dir in $d
do
  cd $dir
  pwd
  f=`find -name \*.o`
  for file in $f
  do
    echo $file:
    $file
  done
  cd ..
done

