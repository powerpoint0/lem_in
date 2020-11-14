#!/bin/zsh

var=$1

if [ "$var" = "" ]; then
  var=h1
fi

h1="--flow-one" # : generates an ant farm with distinctive path and [1] ant in it
h10="--flow-ten" #: generates an ant farm with distinctive path and approximately [10] ants in it
h100="--flow-thousand" #: generates an ant farm with distinctive path and approximately [100] ants in it
h1000="--big" #: generates a big map (approximately [1000] rooms) to test the time complexity
super="--big-superposition" #: generates a big map with overlapping paths

var=$(eval echo "\$$var")

#echo "./generator ${var}"
echo "./generator ${var}" > file.txt

for ((i=1; i < 6; i++))
do
  sleep 1
  MAP=$(./generator ${var})


  echo $MAP > file.txt
  echo $MAP > dir/file$i.txt

  SIZE=+$(echo $MAP | wc -l)
  SIZE=$(echo $SIZE | sed "s/ //g")

#for reading from 0 fd
  LEM=$(time cat  file.txt | ./lem-in)

#for reading from file
#  LEM=$(time ./lem-in file.txt)

  LEM=$(echo $LEM | tail -n $SIZE)

  cat file.txt | wc -l
  echo $LEM | head -n 1
  echo $LEM | tail +3 | wc -l

done
