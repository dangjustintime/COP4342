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
      files[index]=DIR:${files[index]}
      ((num_dir++))
    elif [ -f $file -a ! -x $file ]; then
      ((num_files++))
    elif [ -x $file ]; then
      files[index]=EXE:${files[index]}
      ((num_exe++))
    fi
    ((index++))
  done 
  echo -e "$num_dir directories, $num_files files, $num_exe executables"
  PS1="111111111"
  PS2="222222222"
  PS3="Choose an entry from the list: "
  select file in ${files[*]}; do
    case $file in
      "EXE:"*)
	file=${file:4}
        ;;
      "DIR:"*)
	file=${file:4}
        ;;
      *)
	;;
    esac
    if [[ -z "$file" ]]; then
      echo -e "\nBYE BYE\n"
      exit 1
    elif [ -f $file -a ! -x $file ]; then
      cat $file
      echo -e "\n"
    elif [ -d $file ]; then
      echo $file
    elif [ -x $file ]; then
      echo $file
    else
      echo -e "\n$file"
    fi
  done
done
