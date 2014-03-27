#!/usr/bin/python

import socket
import struct

HOST = '127.0.0.1'
PORT = 3490

# Create a new socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
s.connect((HOST,PORT))

# Identify ourselves as the user interface
s.sendall(struct.pack('i', 1))
data = s.recv(4)

# Tell the server how many locations we will send
s.sendall(struct.pack('ss', "alex", "password"))

# Close the socket
s.close()
