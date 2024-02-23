#########
ROP: 
Return oriented programming is a bin exploitation technique that is useful to gain code execution in the presence of ASLR and DEP/NX protections by re-purposing instructions already present in executable memory space .
The instructions of interest for the technique are pop (take value from stack and put it in a register) followed by a ret and are referred to as "gadgets".
The attacker may change the program's control-flow by over-writing the stack in locations the "gadget" reads from.
Finally by chaining those ("gadgets") together (using the ret statement in each of them) with sufficiently large programs turing -complete functionality is achievable.
