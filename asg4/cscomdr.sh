#!/bin/bash
function getFiles () {
num_dir=0
num_exe=0
num_files=0
index=0
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
files[index]=DIR:..
}

function promptUser () {
echo -e "\n-- cscomdr --"
echo -e "$(pwd)"
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
  if [ -f $file -a ! -x $file ]; then
    cat $file
    echo -e "\n"
  elif [ -d $file ]; then
    cd $file
    getFiles
    break
  elif [ -x $file ]; then
    ./$file
  elif [ "$file" == "q" ]; then
    echo "BYE BYE"
    exit 1
  else
    echo -e "\n$file"
  fi
done
}

getFiles
while true; do
  promptUser
done
