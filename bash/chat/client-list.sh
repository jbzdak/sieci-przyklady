#!/bin/bash

if [ $# -lt 1 ]
then
    echo "USAGE <<ROOM>>>"
    exit 1
fi


source config.sh

exec 5<> /dev/tcp/${HOST}/${PORT}

echo -e "LSTROOM $1" >&5
echo -e "EXT" >&5
cat <&5