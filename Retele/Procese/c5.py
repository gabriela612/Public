

import socket
import pickle
import sys
from struct import *

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
# argv[0] is the python script name, argv[1] - IP of the server, argv[2] - port of the server
s.connect((sys.argv[1], int(sys.argv[2])))
n = (int)(input('n = '))
array = []
numar = pack(">h", n)
s.send(numar)

len_array = s.recv(2)
nr = unpack(">h", len_array)
nr = nr[0]
print("Numarul de divizori : ", nr)

for i in range(nr) :
	rez = unpack(">h", s.recv(2))
	array.append(rez[0])
print("Lista de divizori este : ", array)
s.close()
