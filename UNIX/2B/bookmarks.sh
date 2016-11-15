#!/usr/bin/env bash
show_usage () {                        
  echo "usage: $(basename "$0") [-h|--help] [-s|--save], [-g|--go], [-p|--print], [-d|--delete] <BOOKMARK_NAME> [-l|--list]";
}

show_help () {
  show_usage
  echo 'Options:
  -h, --help          shows help
  -s, --save <BOOKMARK_NAME> saves current directory as bookmark 
  -g, --go <BOOKMARK_NAME> go to bookmark directory (IMPORTANT! USE "." before this command)
  -p, --print <BOOKMARK_NAME> print bookmark directory
  -d, --delete <BOOKMARK_NAME> delete bookmark
  -l, --list list all saved bookmarks   
'
}

function s  {
    # shellcheck disable=SC1091
    source "$BKMRKS";
    CURDIR=$($"PWD");
    validate_bname "$1";
    target=$(eval $(echo echo $(echo \$DIR_$1)));
    if [ -z "$exit_message" ]; then
      if [ -z "$target" ]; then
        echo "export DIR_$1=\"$CURDIR\"" >> "$BKMRKS";
      else
        echo -e "Error: bookmark '${1}' already exists";
      fi;
    fi
}

function g {
     # shellcheck disable=SC1090
    source "$BKMRKS";
    target=$(eval $(echo echo $(echo \$DIR_$1)))
    if [ -d "$target" ]; then #target is an existing catalog
        cd "$target" || exit 1;
    elif [ -z "$target" ]; then #target is empty
        echo -e "Error: bookmark '${1}' does not exist"
    else
        echo -e "Error: '${target}' folder does not exist anymore"
    fi
}

function p {
    # shellcheck disable=SC1090
    source "$BKMRKS"
    target=$(eval $(echo echo $(echo \$DIR_$1)))
    if [ -n "$target" ]; then
      echo $(eval $(echo echo $(echo \$DIR_$1)))
    else
      echo -e "Error: bookmark '${1}' does not exist";
    fi;
    
}

function d {
  # shellcheck disable=SC1090
  source "$BKMRKS"
  validate_bname "$1";
  target=$(eval $(echo echo $(echo \$DIR_$1)))
  if [ -z "$exit_message" ]; then
    if [ -n "$target" ]; then
      unset "DIR_$1";
      sed -i "" "/^export DIR_${1}/d" "$BKMRKS";
    else
      echo -e "Error: bookmark '${1}' does not exist";
    fi;
  fi;
    
}

function l {
    # shellcheck disable=SC1090
    source "$BKMRKS"
    env | sort | awk '/^DIR_.+/{split(substr($0,5),parts,"="); printf("\033[0;33m%-20s\033[0m %s\n", parts[1], parts[2]);}'
}

function validate_bname {
    exit_message=""
    if [ -z "$1" ]; then
        exit_message="Error: bookmark name required"
        echo "$exit_message"
    elif [ "$1" != "$(echo "$1" | sed 's/[^A-Za-z0-9_]//g')" ]; then
        exit_message="Error: Bookmark name is not valid"
        echo "$exit_message"
    fi
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
in "-s"|"--save"*) s "$BOOKMARK_NAME" ;; 
   "-g"|"--go"*) g "$BOOKMARK_NAME" ;;
   "-p"|"--print"*) p "$BOOKMARK_NAME" ;;
   "-d"|"--delete"*) d "$BOOKMARK_NAME" ;;
   "-l"|"--list"*) l ;;
    *) show_usage;;
esac;