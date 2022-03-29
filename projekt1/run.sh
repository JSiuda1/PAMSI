#!/bin/bash

mess_1="I've seen things you people wouldn't believe... Attack ships on fire off the shoulder of Orion..."
mess_2="I watched C-beams glitter in the dark near the Tannhauser Gate. All those moments will be lost in time, like tears in rain... Time to die."


if [[ -d "./build" ]]; then
  cd build 
  cmake clear ../
else
	mkdir build
  cd build
fi


cmake ../
make 
pwd

echo -e "\n \nUruchamianie programu \n \n"

sleep 1

if [ "$1" == "-v" ]; then
  if [[ -n $2 ]]; then
    mess_1=$2
  fi

  if [[ -n $3 ]]; then
    mess_2=$3
  fi
 
  valgrind ./projekt_1 "$mess_1" "$mess_2"
else
  if [[ -n $1 ]]; then
    mess_1=$1
  fi

  if [[ -n $2 ]]; then
    mess_2=$2
  fi
  
  ./projekt_1 "$mess_1" "$mess_2"
fi 


