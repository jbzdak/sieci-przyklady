#!/bin/bash

if [ $# -lt 2 ]
then
    echo "USAGE <<silent|verbose>> <<name>>"
    exit 1
fi

# Tutaj przechopwujemy wiadomości chat (z wielu serwerów)
CHT_ROOM_DIR="/tmp/chtroom/"

mkdir -p $CHT_ROOM_DIR

export VERBOSE=0

if [ $1 -eq silent ]
then
    export VERBOSE=1
fi

# Echo if server is in verbose mode
function mecho{
    if [ ${VERBOSE} ]
    then
        echo $@
    fi
}

# Jeden serwer przechowuje wiadomości ze wszystkich pokojów
# w pliku podanym jako parametr
export CHT_FILE=$CHT_ROOM_DIR"/"$2

function list_room {
    room=$1

    mecho "Messages from room $room:"
    grep "^$room:" ${CHT_FILE} | cut -d: -f2- | sed 's/^/> /'

}

function post {
    chatroom=$1
    __IFS=$IFS
    IFS=
    mecho "submit your message"
    read message
    IFS=${__IFS}
    echo "$chatroom:$message" >> ${CHT_FILE}
}

function list_rooms {
   mecho "Following rooms are used "

   cat /tmp/chtroom/foo | cut -d: -f1 | sort | uniq
}

function help {

    mecho "Options"
    mecho "POST <<chatroom>> -- post message"
    mecho "LSTROOMS -- list all chatrooms"
    mecho "LSTROOM <<chatroom>> -- get messages from chatroom"
    mecho "EXT -- exit from server"
    mecho "? -- this message"

}

# Obcina białe znaki ze zmiennej
function trim
{
    echo $(echo $1 | tr -d [:space:])
}

function menu {
    menu_selection_invalid=1;

    while [ ${menu_selection_invalid} -eq 1 ]
    do

        mecho "Supply next command, ? for help"

        read command a1

        command=$(trim ${command})
        a1=$(trim ${a1})

        case $command in
        "POST")
            post $a1
            menu_selection_invalid=0;
        ;;
        "LSTROOM")
            list_room $a1
            menu_selection_invalid=0;
        ;;
        "LSTROOMS")
            list_rooms
        ;;
        "?")
            help
        ;;
        "EXT")
            exit 0
        ;;
        *) echo "Please select a valid command. Unknown command x${command}x"
        esac
    done
}

mecho "Welcome to one-and-only chat server in bash"

while [ 0 ]
do
    menu
done
