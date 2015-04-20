# Jack Mertens
#
from socket import *
from struct import *

tot = 0

s = socket(AF_INET,SOCK_STREAM)
s.connect(('vortex.labs.overthewire.org', 5842))

#print s.recv(4)

for x in range(4):
	tot+=unpack("<I", s.recv(4))[0]
s.send(pack("<I",(tot & 0xFFFFFFFFF)))
print s.recv(512)
s.close()
