#!/bin/bash

if [ "$1" = "" ];
then
  e="fib karatsuba tutorial"
else
  e=$1
fi
    
for example in $e
do
  cd $example
  if [ -f "_clean.sh" ]; 
  then
    ./_clean.sh
  else
    make clean
  fi
  cd ..
done
