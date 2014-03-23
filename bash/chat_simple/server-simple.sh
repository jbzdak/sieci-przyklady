#!/bin/bash

FILE="/tmp/chatroom-simple"

function read_message {
    __IFS=$IFS
    IFS=
    read message
    IFS=${__IFS}
    echo ${message}
}

echo "submit your message"
message=$(read_message)
echo "${message}" >> ${FILE}
