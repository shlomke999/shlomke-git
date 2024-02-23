#after we ran the server and the client and sent data from input ('while' wireshark open), we need to add the log.log file which contains the (Pre)-Master-Secret to wireshark as decribe here: https://www.comparitech.com/net-admin/decrypt-ssl-with-wireshark/
import socket
import sslkeylog
from ssl import SSLContext, CERT_NONE, PROTOCOL_TLS_CLIENT

ip = "10.30.0.11"
port = 1234
sslkeylog.set_keylog('/home/shlomi/git/cyber/src/SSL-TLS/log.log')  

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
context = SSLContext(PROTOCOL_TLS_CLIENT)
context.load_verify_locations('./cert.pem')
context.check_hostname = False
context.verify_mode = CERT_NONE

client.connect((ip, port))
SSLsock = context.wrap_socket(client, server_hostname=ip)

while True:
    data = input()
    SSLsock.send(data.encode("utf-8")) #send dtat to server
    if "exit" == data:
        exit()
    r = SSLsock.recv(1024)
    print(r.decode('utf-8'))

#Checking if a website has a valid SSL certificate - client side
# import requests
# response=requests.get('https://localhost:60000')
# print(response , "200 = website has valid ssl certificate")