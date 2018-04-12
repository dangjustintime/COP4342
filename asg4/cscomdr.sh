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
  if [ -z $file ]; then
    echo "no entry chosen"
    echo "bye bye"
    exit 1
  elif [ $file == "secret" ]; then
    echo "I have a secret"
    $has_key=0
    for $temp in ${files[*]}; do
      if [ "$key" = "secret.key"]; then
        $temp = $(touch secret.key)
	$has_key=1
	$key = $temp
      fi
    done

    if [ $has_key = 0 ]; then
      read -rsn1 -p "Enter key: " key < /dev/tty
    fi
    openssl enc -d -a -k $key -aes-256-cbc -in secret
    touch secret
  elif [ -f $file -a ! -x $file ]; then
    cat $file
    echo -e "\n"
  elif [ -d $file ]; then
    cd $file
    getFiles
    break
  elif [ -x $file ]; then
    ./$file
  fi
done
}

trap "echo type SPACE to exit" SIGINT SIGTERM

# main function
getFiles
while true; do
  promptUser
done
