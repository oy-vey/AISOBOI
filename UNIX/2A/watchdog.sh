#!/bin/bash
HTML=$(wget -qO - "vk.com/$1")
if [ -n "$HTML" ]
then
isHidden=$(echo $HTML | grep -o "Страница доступна только авторизованным пользователям")
isOffline=$(echo $HTML | grep -o "заходил")
if [ -n "$isHidden" ]
then
echo "Hidden information"
else
if [ -n "$isOffline" ]
then
echo "Offline"
else
echo "Online"
fi
fi
else
echo "Page does not exists"
fi