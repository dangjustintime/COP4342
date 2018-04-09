#!/bin/bash
while true; do
  echo -e "\n-- cscomdr --"
  echo -e "$(pwd)"
  FILES=($(ls))
  PS3="Choose an entry from the list: "
  select FILE in ${FILES[*]}; do
    if [[ -z "$FILE" ]]; then
      echo -e "\nfile not chosen\n"
    elif [[ "$FILE" = "q" ]]; then
      echo -e "\nBYE BYE\n"
      exit 1
    else
      echo -e "\n$FILE"
    fi
  done
done
