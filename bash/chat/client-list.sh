#!/bin/bash

source config.sh
exec 5<> /dev/tcp/${HOST}/${PORT}

echo -e "LSTROOM FOO\n" >&5
echo -e "EXT" >&5
cat <&5