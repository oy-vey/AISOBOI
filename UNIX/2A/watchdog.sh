#!/bin/bash
HTML=$(wget -qO - "vk.com/$1")
if [ -n "$HTML" ]
then
isHidden=$(echo $HTML | grep -o "�������� �������� ������ �������������� �������������")
isOffline=$(echo $HTML | grep -o "�������")
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