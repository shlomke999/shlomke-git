ex1:
take a big dictionary file and run:
dnsenum -f dic.txt ilrd.co.il

ex3:
nmap -sU 67.199.248.12 (one of the hosts found in dnsenum)
nmap -sT 67.199.248.12 (one of the hosts found in dnsenum)

ex4:
dirb https://67.199.248.12

ex5:
nmap -sP 10.1.0.0/16
nmap -sn 10.1.0.0/16

ex6:
nmap on one host found in ex5

ex7:
crunch 10 10  0123456789 0123456789 -o phone_numbers.txt -t 05,%%%%%%%%

