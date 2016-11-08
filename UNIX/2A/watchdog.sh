#!/bin/bash

show_usage () {                        
  echo "usage: $(basename "$0") [-h|--help] <USERID>";
}

show_help () {
  show_usage
  echo 'Returns "User is online"  if vk.com/<USERID> user is online
-	"User is offline" if vk.com/<USERID> user is offline
-	"Hidden profile" if vk.com/<USERID> user is hidden
Options:
  -h, --help          shows help
Exit status:
  1: Invalid user
  0: Valid user
'
}

if [ "$#" == "0" ]; then
  show_usage;
  exit;
fi

# Do it simple
if [ "$1" == "-h" ] || [ "$1" == "--help" ]; then 
  show_help;
  exit;
fi



user_id=$1;
RESPONSE=$(wget -qO - "https://api.vk.com/method/users.get?user_ids=$user_id&fields=online");
is_invalid=$(echo "${RESPONSE}" | grep -Po '(?<="error_code":)[0-9]+');
error_msg=$(echo "${RESPONSE}" | grep -oP '"error_msg":"\K[^"]+');
if [ -n "${is_invalid}" ]; then
	(echo >&2 "Error: " "${error_msg}"; exit 1;)
fi;
is_hidden=$(echo "${RESPONSE}" | grep -Po '(?<="hidden":)[0-9]+');
is_online=$(echo "${RESPONSE}" | grep -Po '(?<="online":)[0-9]+');
if [ -n "${is_hidden}" ]; then
	notify-send "Hidden profile";
else
	case "${is_online}" in "1"*) notify-send "User is online" ;; "0"*) notify-send "User is offline" ;; esac;
fi;