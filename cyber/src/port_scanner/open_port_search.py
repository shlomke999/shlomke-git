import pyfiglet
import sys
import socket
from datetime import datetime

if len(sys.argv) == 2:	
	target = sys.argv[1]#the ip to scan
else:
	print("Invalid amount of Argument, enter ip to scan")

print("Scanning Target: " + target)

for port in range(1,65535):
	#AF_INET is the address familly SOCK_STREAM is the sock type
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	
	# check if port is open with connect_ex func
	result = s.connect_ex((target,port))
	if result == 0:
		print(f"Port {port} is open")
	s.close()
		

