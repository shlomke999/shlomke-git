###ex1:

dns cnn responses: 

cnn.com: type A, class IN, addr 151.101.67.5
cnn.com: type A, class IN, addr 151.101.3.5
cnn.com: type A, class IN, addr 151.101.195.5
cnn.com: type A, class IN, addr 151.101.131.5



sudo iptables -A INPUT -s 151.101.67.5 -j DROP

אחרי שחוסמים את האייפי הראשון, יהיה ניסיון לעשות TCP HANDSHAKE  מול אייפי אחר מהריספונס 

###ex2: reject http and only allow https

http://info.cern.ch/

sudo iptables -A INPUT -p tcp --sport http -j DROP
sudo iptables -A OUTPUT -p tcp --sport http -j DROP



###ex3: block pings 

sudo iptables -A INPUT -p icmp -j DROP
sudo iptables -A OUTPUT -p icmp -j DROP

To clear all the currently configured rules, you can issue the flush command:
iptables -F

###ex4: allow only one ssh at a time :

sudo iptables -A INPUT -p tcp --dport 22 -m connlimit --connlimit-above 1 --connlimit-mask 0  -j REJECT


###ex5: enable ssh req on port 500 only from specific machine


sudo iptables -A INPUT -p tcp -s 10.1.0.192 --dport 500 -j ACCEPT
June 7, 2023







