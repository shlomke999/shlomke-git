import socket
import sys

def ScanPortOnAllNetwork():
    ip = sys.argv[1]
    port = sys.argv[2]
    net_ip = '.'.join(ip.split('.')[:3])
    for i in range(1, 255):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(0.001)
         
        curr_ip = f"{net_ip}.{i}"
        result = s.connect_ex((curr_ip, int(port)))

        if result == 0:
            print(f"Port {port} is open on {curr_ip}")
        s.close()

ScanPortOnAllNetwork()

