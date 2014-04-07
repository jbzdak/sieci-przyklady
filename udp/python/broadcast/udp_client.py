# -*- coding: utf-8 -*-
import socket

UDP_IP = "192.168.1.255"
UDP_PORT = 5005
MESSAGE = "Hello, World!"

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

sock.settimeout(1)

try:
    response = sock.recv(1024)
    print(response)
except socket.timeout:
    print("No response")