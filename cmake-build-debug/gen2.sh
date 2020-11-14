#!/bin/zsh

files=($(ls not_valid))

for file in "${files[@]}"
do
  sleep 1
  echo ______________________ $file _____________________

  cat not_valid/$file > file.txt
  ./lem-in < file.txt
done