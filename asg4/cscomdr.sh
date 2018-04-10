#!/bin/bash
while true; do
  echo -e "\n-- cscomdr --"
  echo -e "$(pwd)"
  FILES=($(ls))
  for FILE in FILES; do
    if [ -f $FILE ]; then
      echo "$FILE is a file"
    elif [ -d $FILE ]; then
      echo "$FILE is a directory"
    fi
  done 
  PS3="Choose an entry from the list: "
  select FILE in ${FILES[*]} q; do
    if [[ -z "$FILE" ]]; then
      echo -e "\nBYE BYE\n"
      exit 1
    else
      echo -e "\n$FILE"
    fi
  done
done
