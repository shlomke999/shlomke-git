#include <stdio.h>

/*
mission: insert lines in the marked area so the program will run finish function without calling it.
compile with these flags gcc -Wall -Wextra -g3 -no-pie provided2.c 
my way of action: checked what is dereference of the return address of func and checked with disass on GDB 
how much should i substruct from it to go to the assembly command for the last printf in finish func.

the way to check the return address of func: info frame command, it's the eip register in the saved registers.
"*/

void finish(int a, int b) 
{
  if (42 == a) 
  {
    printf("That's an interesting value for a.\n");
  }
  if (0 == b)
  {
    printf("How mundane.\n");
  }
  if (32767 == a * b) {
    printf("Keep in mind that neither success not failure is ever final.\n");
  }
  if (8001 == a * b || 9001 == a * b) 
  {
    printf("Realize that while the first 90 percent of code accounts for 90 "
           "percent of the development time, so does the last 10 percent of "
           "the code.");
  }

  printf("You've successfully finished this part of the exercise.\n");
}

void func()
 {
	// Add code here
  int a = 42, b = 0;
  *(&a + 6) = (char *)(func - 18);
}

int main() 
{
  func();

  return 0;
}
