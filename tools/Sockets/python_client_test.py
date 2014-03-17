#!/usr/bin/python
# Echo client program
import socket
import struct

HOST = '127.0.0.1'
PORT = 3490

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))
#for i in range(0,4):
#    s.sendall(struct.pack('ddd',i,23.4,45.6))

for i in range (0,10):

    s.sendall(struct.pack('ddd', 0, 0, 0))

    data = s.recv(8)
    print 'Recieved', repr (data)

s.close()
