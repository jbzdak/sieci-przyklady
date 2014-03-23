# -*- coding: utf-8 -*-
import multiprocessing

import socket
import threading

HOST = 'localhost'                 # Symbolic name meaning all available interfaces
PORT = 5555               # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)


def handle(conn, add):
    while 1:
        data = conn.recv(1024)
        if not data: break
        conn.sendall(data)
    conn.close()

while True:
    conn, addr = s.accept()
    print('Connected by', addr)
    t = multiprocessing.Process(target=handle, args=(conn,addr))
    t.start()
