ex1:
- the assemblly code is doing as follows - get argument from user, and return the sum of all numbers from 0 to the number.
- rsi is the argv argument. rsi + 8 is 8 byte forward wich is the argument we enter when runnung the file.
- xor eax, eax is emptying the eax regisrer.


ex2:
- it does exactlly what ex1 assemblly does - get argument from user, and return the sum of all numbers from 0 to the number.
- weired: 1. can't debug it in gdb cause it gets termination signal. 2. when i look at the assemblly i see only mov commands.
- how it's possible: it's some sort of optimization. for example if we have -
mov [x], 0 
mov [y], 1
and we want to check if y = x
we can write mov R,[x]
for explenation on how this work exactly see - https://hackaday.com/2021/05/21/one-instruction-to-rule-them-all-c-compiler-emits-only-mov/


ex3:
- the file that was compilated and then disassembled is using mov commands when assigning values, because
  it knowshow much to allocate because of the compilation process and its optimizations.
  the file that was'nt fully compilated, but only until the assembler part, is using the expensive movq  instruction.
- another difference: the file that was'nt fully compilated is looking for our bst functions in the @plt
  and has no idea that the functions are on the .h file cause the linker did'nt come yet.


ex4:
1. strings <filename> | grep pass
2. objdump -s -j .rodata <filename>
3. in gdb we see in main a call to strlen, and then cmp instruction to main + 117, and in main + 117 area 
   we see memcmp call on two addresses wich we can assume that are the check for the password validity.
   so we print the address: p (char *)(0x5555...) and there is our password.

ex5:
way 1:
	1. strings <filename> | grep /
	2. look at the output and find the explenation why the file is blocked for everything.(ther's a website mentioned)
	3. go to the mentioned website and download the compression tool.
	4. decompress the file.
	5. we have the same file as in ex4
	
way 2:
1.download idafree.
2. open the file with it.
3. go to search, text, search for "pass"
4. we found the password.
