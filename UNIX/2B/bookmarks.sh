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
Exit status:
  1: Invalid user
  0: Valid user
'
}

s {
    _bookmark_name_valid "$@"
    if [ -z "$exit_message" ]; thenDI
        CURDIR=$(echo $PWD| sed "s#^$HOME#\$HOME#g")
        echo "export DIR_$1=\"$CURDIR\"" >> $BKMRKS
    fi
}



if [ "$#" == "0" ]; then
  show_usage;
  exit;
fi

if [ "$1" == "-h" ] || [ "$1" == "--help" ]; then 
  show_help;
  exit;
fi


# setup hidden file to store bookmarks
if [ ! -n "$BKMRKS" ]; then
    BKMRKS=~/.bkmrks
fi
touch $BKMRKS

