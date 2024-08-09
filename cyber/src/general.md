1. Kerberoasting attack: attackers initiate a request for a service from the dc itself, that way there is no 
  validation that the user has permissions for that service, and then get back service ticket encrypted with the 
  SPN's password hash. then use a tool like  GetUserSPNs tool, which is often used to perform Kerberoasting 
  attack.
  All major open-source tools, like Impacket and Rubeus, request tickets in RC4 encryption type.(easily cracked). 
3. url composed of: protocol, domain, path, request(the "?"), and parameter.
