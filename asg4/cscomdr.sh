#!/bin/bash
while true; do
  num_dir=0
  num_exe=0
  num_files=0
  echo -e "\n-- cscomdr --"
  echo -e "$(pwd)"
  FILES=($(ls))
  for FILE in ${FILES[*]}; do
    if [ -d $FILE ]; then
      ((num_dir += 1))
    elif [ -f $FILE -a ! -x $FILE ]; then
      ((num_files += 1))
    elif [ -x $FILE ]; then
      ((num_exe+= 1))
    fi
  done 
  echo -e "$num_dir directories, $num_files files, $num_exe executables"
  PS3="Choose an entry from the list: "
  select FILE in ${FILES[*]}; do
    if [[ -z "$FILE" ]]; then
      echo -e "\nBYE BYE\n"
      exit 1
    elif [ -f $FILE -a ! -x $FILE ]; then
      cat $FILE
      echo -e "\n"
    elif [ -d $FILE ]; then
      cd $FILE
    elif [ -x $FILE ]; then
      ./$FILE
    else
      echo -e "\n$FILE"
    fi
  done
done
