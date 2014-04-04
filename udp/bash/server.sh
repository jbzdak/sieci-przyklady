#!/bin/bash

CHT_FILE="/tmp/chatroom"
CLIENT_LIST="/tmp/client-list"

source config.sh

# Obcina białe znaki ze zmiennej
function trim()
{
    echo $(echo $1 | tr -d [:space:])
}

function post {
    __IFS=$IFS
    IFS=
    read message
    IFS=${__IFS}
    echo "$message" >> ${CHT_FILE}
}

function save_remote(){

    echo "$1:${PORT}" >> ${CLIENT_LIST}

}

function do_own_ping(){

    if [ $1 != ${IP} ]
    then
        echo PING ${IP}  | ncat -u 255.255.255.255 8000
    fi
}


function menu(){
    menu_selection_invalid=1;

    read command p1 p2

    echo ${command} >&2

    command=$(trim ${command})
    p1=$(trim ${p1})
    p2=$(trim ${p2})

    case $command in
    "PING")
        save_remote ${p1}
        do_own_ping  ${p1}
    ;;
    "POST")
        post
    ;;
    "?")
        help
    ;;
    *)
        echo "Please select a valid command. Unknown command '${command}'"
        help
    ;;
    esac

}

menu