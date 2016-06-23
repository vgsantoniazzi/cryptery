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
  if [ -f "_runall.sh" ]; 
  then
    ./_runall.sh
  else
    make run
  fi
  cd ..
done
