#include <stdlib.h>/*exit*/
#include <sys/types.h>/*fork*/
#include <unistd.h>/*exec*/
#include<stdio.h>/*print*/
#include <string.h>/*strncmp*/
#include <sys/wait.h>/*wait*/

#define MAX_CHARS 50

/*status: approved.
by: michael evanov.*/
int ForkFunc(char input[])
{
	char *arg_list[MAX_CHARS]; 
	int i = 1;
		
	arg_list[0] = strtok(input, " ");
	while (1)
	{
        arg_list[i] = strtok(NULL, " ");
       	if (NULL == arg_list[i])
		{
			break;
		}
		++i;
	}			
	/* this is the child */
	if (fork() == 0)
	{
		execvp (arg_list[0], arg_list);		
		/* The execvp function returns only if an error occurs. */
		printf ("command not found\n");
	}
	/*this is the parent process*/
	else
	{
		wait(0);
	}
	return 0;	
}	


void ShellInit()
{
	int is_fork = 1;
	char input[MAX_CHARS];
	
	printf("type a command, type fork/system to change between the two, exit to exit: \n");
	while (1)
	{
		fgets(input, 50, stdin);  
		*(input + strlen(input) - 1) = '\0';
		if (0 == strcmp(input, "exit"))
		{
			exit(0);
		}
		if (0 == strcmp(input, "system"))
		{
			is_fork = 0; 
			printf("running with system now:");
			continue; 
		}
		if (0 == strcmp(input, "fork"))
		{
			is_fork = 1; 
			printf("running with fork now:");
			continue; 
		}				
		if (is_fork == 0)
		{
			system(input);
			continue;
		}
		else
		{
			ForkFunc(input);
			continue;
		}
	}	
}

int main()
{
	ShellInit();
	return 0;
}
