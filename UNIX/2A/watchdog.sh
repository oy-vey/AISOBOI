#!/bin/bash
user_id=$1;
RESPONSE=$(wget -qO - "https://api.vk.com/method/users.get?user_ids=$user_id&fields=online");
is_valid=$(echo "${RESPONSE}" | grep -Po '(?<="error_code":)[0-9]+');
error_msg=$(echo "${RESPONSE}" | grep -oP '"error_msg":"\K[^"]+');
if [ -n "${is_valid}" ]; then
	echo "Error: " "${error_msg}"; exit 1;
fi;
is_hidden=$(echo "${RESPONSE}" | grep -Po '(?<="hidden":)[0-9]+');
is_online=$(echo "${RESPONSE}" | grep -Po '(?<="online":)[0-9]+');
if [ -n "${is_hidden}" ]; then
	echo "Hidden profile";
else
	case "${is_online}" in "1"*) echo "User is online" ;; "0"*) echo "User is offline" ;; esac;
fi;
