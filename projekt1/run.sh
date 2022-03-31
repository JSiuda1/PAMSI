#!/bin/bash

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

  if [[ -n $3 ]] && [[ -n $2 ]]; then
    mess_1=$1
    mess_2=$3
    valgrind ./projekt_1 "$mess_1" "$mess_2"
  else 
    valgrind ./projekt_1
  fi
else
  if [[ -n $1 ]] && [[ -n $2 ]]; then
    mess_1=$1
    mess_2=$2
    ./projekt_1 "$mess_1" "$mess_2"
  else 
    ./projekt_1
  fi

fi 


