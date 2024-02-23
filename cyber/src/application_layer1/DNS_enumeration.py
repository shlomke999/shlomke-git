import dns.resolver
from dns.rdtypes.ANY import NSEC

def DNSEnum():
	target_domain = "walla.co.il"
	resolver = dns.resolver.Resolver()
	dic = open('words.txt', 'r')
	words = dic.readlines()
	for word in words:
		curr_enumerate = word.replace('\n', '.') + target_domain
		try:
			answer = resolver.resolve(str(curr_enumerate), "A")
			print(f'curr enumeration: {curr_enumerate}')
			for a in answer:
				print(f'{a}')
		except (dns.resolver.NoAnswer, dns.resolver.NXDOMAIN, dns.name.EmptyLabel):
			pass
		
DNSEnum()
