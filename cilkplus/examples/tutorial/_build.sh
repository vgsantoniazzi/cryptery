#!/bin/bash

d="array-notations reducers"

for dir in $d
do
  cd $dir
  pwd
  f=`find -name \*.cpp`
  for file in $f
  do
    $CXX $CXXFLAGS -o $file.o $COPTS $file
  done
  cd ..
done

