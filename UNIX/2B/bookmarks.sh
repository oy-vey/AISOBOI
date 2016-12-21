#!/usr/bin/env bash


show_help () {
  echo 'After executing "source bookmarks.sh" the following commands will be available:
  s <BOOKMARK_NAME> - saves current directory as bookmark
  g <BOOKMARK_NAME> - go to bookmark directory
  p <BOOKMARK_NAME> - print bookmark directory
  d <BOOKMARK_NAME> - delete bookmark
  l list all saved bookmarks
'
}

RED="0;31m"
GREEN="0;33m"

function s {
    # shellcheck disable=SC1091
    source "$BKMRKS";
    CURDIR=$(echo $PWD | sed 's/\"/\\"/g');
    validate_bname "$1";
    eval "target=\$DIR_$1";
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
    eval "target=\$DIR_$1"
    if [ -d "${target}" ]; then #target is an existing catalog
        cd "${target}" || exit 1;
    elif [ -z "${target}" ]; then #target is empty
        echo -e "Error: bookmark '${1}' does not exist"
    else
        echo -e "Error: '${target}' folder does not exist anymore"
    fi
}

function p {
    # shellcheck disable=SC1090
    source "$BKMRKS"
    eval "target=\$DIR_$1"
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
  eval "target=\$DIR_$1"
  if [ -z "$exit_message" ]; then
    if [ -n "$target" ]; then
      unset "DIR_$1";
      sed -i "/^export DIR_${1}/d" "$BKMRKS";
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

show_help;

#autocompleteion

function _l {
    source $BKMRKS
    env | grep "^DIR_" | cut -c5- | sort | grep "^.*=" | cut -f1 -d "="
}

function _comp {
    local curw
    COMPREPLY=()
    curw=${COMP_WORDS[COMP_CWORD]}
    COMPREPLY=($(compgen -W '`_l`' -- $curw))
    return 0
}

# ZSH completion command
function _compzsh {
    reply=($(_l))
}


# setup hidden file to store bookmarks
if [ ! -n "$BKMRKS" ]; then
    BKMRKS=~/.bkmrks
fi
touch $BKMRKS



# bind completion command for g,p,d to _comp
if [ $ZSH_VERSION ]; then
    compctl -K _compzsh g
    compctl -K _compzsh p
    compctl -K _compzsh d
else
    shopt -s progcomp
    complete -F _comp g
    complete -F _comp p
    complete -F _comp d
fi