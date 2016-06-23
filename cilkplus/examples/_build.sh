#!/bin/bash

if [ "$1" = "" ];
then
  echo "Usage: ./_build.sh <example-name> [<build-options>]"
  echo "Or:    ./_build.sh all [<build-options>]"
  exit
fi
    
if [ "$1" = "all" ];
then
  e="fib karatsuba tutorial"
else
  e=$1
fi

if [ "$2" != "" ];
then
  OPT=$2
else
  OPT="-O3"
fi
    
BUILD_HOME=`pwd`
BUILD_FLAGS="-fcilkplus -I$BUILD_HOME/../lib -L$BUILD_HOME/../lib -ldl -march=native $OPT"
    
export LD_LIBRARY_PATH="$BUILD_HOME/../lib:$LD_LIBRARY_PATH"
export PATH="$BUILD_HOME/../bin:$PATH"
export CXX=clang++
export CC=clang
export CXXFLAGS=$BUILD_FLAGS
export CFLAGS=$BUILD_FLAGS

for example in $e
do
  cd $example
  if [ -f "_build.sh" ]; 
  then
    ./_clean.sh
    ./_build.sh
  fi
  if [ -f "Makefile" ]; 
  then
    make clean
    make build
  fi
  cd ..
done

