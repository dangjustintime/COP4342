#!/bin/bash
while true; do
  num_dir=0
  num_exe=0
  num_files=0
  index=0
  echo -e "\n-- cscomdr --"
  echo -e "$(pwd)"
  files=($(ls))
  for file in ${files[*]}; do
    if [ -d $file ]; then
      files[index]="DIR:${files[index]}"
      ((num_dir++))
    elif [ -f $file -a ! -x $file ]; then
      ((num_files++))
    elif [ -x $file ]; then
      files[index]="EXE:${files[index]}"
      ((num_exe++))
    fi
    ((index++))
  done 
  echo -e "$num_dir directories, $num_files files, $num_exe executables"
  PS3="Choose an entry from the list: "
  select file in ${files[*]}; do
    if [[ -z "$file" ]]; then
      echo -e "\nBYE BYE\n"
      exit 1
    elif [ -f $file -a ! -x $file ]; then
      cat $file
      echo -e "\n"
    elif [ -d $file ]; then
      echo ${file:3}
    elif [ -x $file ]; then
      echo ${file:3}
    else
      echo -e "\n$file"
    fi
  done
done
