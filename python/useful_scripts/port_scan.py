from scapy.all import ICMP, IP, sr1, TCP
from scapy.all import *

server_to_scan = "10.1.0.133"
my_ip = get_if_addr("enx00e04c680256")

ip = IP(src=str(my_ip), dst=str(server_to_scan))

for i in range(1024):
     syn_packet = TCP(sport=15500, dport=i, flags="S")
     resp = sr1(ip/syn_packet, timeout=0.1, verbose=0) #send syn packet to the server
     
     if (resp is None):
         print(f"port{i} is closed or host is down")
     elif (resp.getlayer(TCP).flags == "SA"): 
         print(f"port{i} is open")
     else:
         print(f"got reset from port{i}")
         