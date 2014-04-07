# -*- coding: utf-8 -*-
import socket
import struct
import sys

message = 'very important data'
multicast_group = ('224.3.29.71', 9000)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.settimeout(0.2)

try:

    # Send data to the multicast group
    print('sending "%s"' % message)
    sent = sock.sendto(message, multicast_group)

    # Look for responses from all recipients
    while True:
        print('waiting to receive')
        try:
            data, server = sock.recvfrom(16)
        except socket.timeout:
            print('timed out, no more responses')
            break
        else:
            print('received "%s" from %s' % (data, server))

finally:
    print('closing socket')
    sock.close()