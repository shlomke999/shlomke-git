#include <stdio.h>

/*
mission: insert lines in the marked area so the program will print only "num is now 3
compile with these flags gcc -Wall -Wextra -g3 -m32 -no-pie provided.c 
my way of action: checked what is dereference of the return address of func and checked with disass on GDB 
how much should i add to it to skip the assembly command for num = 4, and 10 was the answer.

the way to check the return address of func: info frame command, it's the eip register in the saved registers.
"*/


void func(long a, long b)
{
    // Insert lines here
    *(&a - 1) += 10;        
    return;

    printf("%ld\n", b);
    printf("%ld\n", a);
}

int main()
{
    int num = 3; /*run this line*/
    func(3, 1); /*skip*/
    num = 4; /*skip*/
    printf("num is now %d\n", num); /*continue*/

    return 0;
}
