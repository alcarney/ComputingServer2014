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

data = struct.unpack('d', s.recv(8))
print 'Recieved', repr (data)

s.sendall(struct.pack('ddd', 0, 0, 0))

data = struct.unpack('d', s.recv(8))
s.close()
print 'Recieved', repr (data)
