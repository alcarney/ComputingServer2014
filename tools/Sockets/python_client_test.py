#!/usr/bin/python
# Echo client program
import socket
import struct

HOST = '127.0.0.1'
PORT = 3490

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))
s.sendall(struct.pack('ddd',1,23.4,45.6))
#data = s.recv(1024)
s.close()
#print 'Recieved', repr (data)
