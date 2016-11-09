#!/usr/bin/env bash
show_usage () {                        
  echo "usage: $(basename "$0") [-h|--help] [-s|--save], [-g|--go], [-p|--print], [-d|--delete] <BOOKMARK_NAME> [-l|--list]";
}

show_help () {
  show_usage
  echo 'Options:
  -h, --help          shows help
  -s, --save <BOOKMARK_NAME> saves current directory as bookmark 
  -g, --go <BOOKMARK_NAME> go to bookmark directory
  -p, --print <BOOKMARK_NAME> print bookmark directory
  -d, --delete <BOOKMARK_NAME> delete bookmark
  -l, --list list all saved bookmarks   
'
}

changedir () {
  newdir=$1;
  cd $newdir;
}

function s  {
    CURDIR=$(echo $PWD);
    echo "export DIR_$1=\"$CURDIR\"" >> $BKMRKS;
}

function g {
    source $BKMRKS
    target="$(eval $(echo echo $(echo \$DIR_$1)))" #TBD
    if [ -d "$target" ]; then #target is an existing catalog
        changedir $target;
    elif [ ! -n "$target" ]; then #target is empty
        echo -e "\033[${RED}WARNING: '${1}' bashmark does not exist\033[00m"
    else
        echo -e "\033[${RED}WARNING: '${target}' does not exist\033[00m"
    fi
}

function p {
    source $BKMRKS
    echo "$(eval $(echo echo $(echo \$DIR_$1)))"
}

function d {
    unset "DIR_$1";
}

function l {
    source $BKMRKS
    env | sort | awk '/^DIR_.+/{split(substr($0,5),parts,"="); printf("\033[0;33m%-20s\033[0m %s\n", parts[1], parts[2]);}'
}

command=$1;
BOOKMARK_NAME=$2;

if [ "$#" == "0" ]; then
  show_usage;
  exit;
fi

if [ "$command" == "-h" ] || [ "$command" == "--help" ]; then 
  show_help;
  exit;
fi

# setup hidden file to store bookmarks
if [ ! -n "$BKMRKS" ]; then
    BKMRKS=~/.bkmrks
fi
touch $BKMRKS

case "${command}" 
in "-s"|"--save"*) s $BOOKMARK_NAME ;; 
   "-g"|"--go"*) g $BOOKMARK_NAME ;;
   "-p"|"--print"*) p $BOOKMARK_NAME ;;
   "-d"|"--delete"*) d $BOOKMARK_NAME ;;
   "-l"|"--list"*) l ;;esac;