#!/bin/bash


if [ $# -lt 1 ]
then
    echo "USAGE <<ROOM>>>"
    exit 1
fi


source config.sh

message=$2

exec 5<> /dev/tcp/${HOST}/${PORT}

echo -e "POST $1" >&5


echo ${message} >&5

echo -e "EXT" >&5

cat <&5