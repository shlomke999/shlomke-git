# Creating the private key and cert:  openssl req -newkey rsa:2048 -new -nodes -x509 -days 3650 -keyout key.pem -out cert.pem
# instructions on how to save ssl keys to view tls traffic:  https://my.f5.com/manage/s/article/K50557518  
import socket
import ssl

ip = "10.30.0.11"
port = 1234

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
context.load_cert_chain('./cert.pem', './key.pem')

server.bind((ip, port))
server.listen(1)
connection, client_address = server.accept()
SSLSock = context.wrap_socket(connection, server_side=True)
while True:
    data = SSLSock.recv(1024)
    if "exit" == data.decode('utf-8'):
        print("bye bye")
        exit()
    print(f"Received: {data.decode('utf-8')}")
    SSLSock.send(data)



