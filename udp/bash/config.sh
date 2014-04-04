#!/bin/bash

DEVICE=wlan0
IP=$(/sbin/ifconfig ${DEVICE} | sed -En 's/.*inet (addr:)?(([0-9]*\.){3}[0-9]*).*/\2/p')
PORT=8000