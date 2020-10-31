#!/bin/zsh

var=$1

h1="--flow-one" # : generates an ant farm with distinctive path and [1] ant in it
h10="--flow-ten" #: generates an ant farm with distinctive path and approximately [10] ants in it
h100="--flow-thousand" #: generates an ant farm with distinctive path and approximately [100] ants in it
h1000="--big" #: generates a big map (approximately [1000] rooms) to test the time complexity
super="--big-superposition" #: generates a big map with overlapping paths

var=$(eval echo "\$$var")

#echo "./generator ${var}"
echo "./generator ${var}" > file.txt

for ((i=1; i < 10; i++))
do
  sleep 1
  A=$(./generator ${var})

  MAP=$(echo $A | head -n 1)

  MAP=$MAP\\n$(echo $A | tail -n +3)

  echo $MAP > file.txt

  SIZE=+$(echo $MAP | wc -l)
  SIZE=$(echo $SIZE | sed "s/ //g")

  LEM=$(./lem_in file.txt | tail -n $SIZE)

#LEM=$(./lem_in file.txt)

  cat file.txt | wc -l
  echo $LEM | head -n 1
  echo $LEM | wc -l

done