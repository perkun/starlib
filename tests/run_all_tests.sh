#!/bin/bash
# created by perkun on 07/10/2021

while IFS= read -r line; do
  PROG=`echo $line | cut -d ' ' -f 2 | cut -d '"' -f 2`
  cd $PROG/bin/Debug
  echo RUNNING TEST: $PROG
  ./$PROG
  echo
  cd ../../../
done < premake5.lua
