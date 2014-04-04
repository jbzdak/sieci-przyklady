#!/bin/bash
__IFS=$IFS
IFS=
read message
IFS=${__IFS}

echo ${message} >&2
echo "OK"

