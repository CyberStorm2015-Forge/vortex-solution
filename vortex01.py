#!/bin/usr/python3
from socket import *
from struct import *

if __name__ == '__main__':
    host = "vortex.labs.overthewire.org"
    port = 5842

    sock = socket(AF_INET, SOCK_STREAM)
    sock.connect((host, port))

    sum = 0
    
    for i in range(4):
        data = sock.recv(4)
        sum += unpack("<I", data)[0]

    sock.send(pack("<I", (sum & 0xFFFFFFFF)))
    print(sock.recv(1024))
    
    sock.close()
