from ipaddress import *
from scapy.all import ICMP, IP, sr1

count = 0
network = ip_network('10.1.0.23/24', strict=False)

for host in network.hosts():
    resp = sr1(IP(dst=str(host)) /ICMP(), timeout=2, verbose=0)
    
    if resp is None:
        print(f"{host} is down or not responding")   
    else:
        print(f"{host} is responding")
        count +=1

print(f"{count}/{network.num_addresses} hosts are up")


