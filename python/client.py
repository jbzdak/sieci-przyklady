# -*- coding: utf-8 -*-

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("google.pl", 80))
s.send("GET / HTTP/1.0\n\n")
data = s.recv(1000)

print(data)
print("Reclieved {} bytes".format(len(data)))