#!/bin/bash
while true; do
  echo -e "\n-- cscomdr --"
  echo -e "$(pwd)"
  FILES=($(ls))
  select FILE in ${FILES[*]}; do
    if [ "$FILE" == "q"]; then
      echo -e "\nBye Bye"
      break;
    fi
    
  done
done
