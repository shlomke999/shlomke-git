#define _POSIX_SOURCE 500
#define _POSIX_C_SOURCE 199309L
#include <stdio.h> /*printf*/
#include <sys/types.h> /*getpid*/
#include <unistd.h> /*getpid*/
#include <sys/wait.h> /*wait*/
#include <signal.h> /*sigaction*/
#include <unistd.h>/*exec*/
#include <stdlib.h>/*system*/
#include <string.h>/*strlen*/

static volatile pid_t pid = 0;



static void SIG2Handler()
{
    printf("parent: recived SIG2 signal\n");
}


void handler1(int signum, siginfo_t *info, void *n)
{
	char *print = "Recived SIGUSR2\n";
	size_t len = strlen(print);
	write(STDOUT_FILENO, print, len);
	pid = info->si_pid;
}

/* Status : approved.
 * Reviewer : nevo
 * Arguments : process full path
 * Return : void.
 * Special Notes : 
 */
void ex4(char *command)
{
	pid_t parent;
	struct sigaction sa;
	char parent_pid[64];
	char command_line[255];
	int i = 0, ret = 0;
	parent = getpid();
	sa.sa_sigaction = handler1;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR2, &sa, NULL);	
	sprintf(parent_pid, " %d &", parent);
	strcat(command_line, command);
	strcat(command_line, parent_pid);   
	ret = system(command_line);
	if (127 == ret || -1 == ret)
	{
		perror("error occured: ");
	}
	for (i = 0; i < 5; ++i)
	{
		pause();
		kill(pid, SIGUSR1);
	}
}





int main()
{
	struct sigaction child;
    child.sa_handler = SIG2Handler;
	char *arg_list[255] = {"./test.out", "NULL"}; 
	int res = fork();
	
	if (res == 0) /* this is the child */
	{		
			printf ("hi, i'm child procces pid: %d\n", getpid());
			execvp(arg_list[0], arg_list);
	}
	
		
	else	/*this is the parent*/
	{
			sleep(1);
			sigaction(SIGUSR2, &child, NULL);
			kill(res, SIGUSR1);  /*send child SIGUSR1 signal*/
			pause();
			wait(0);
			printf("hi, i'm parent procces pid: %d\n", getpid());
	}
	ex4("/home/shlomi/git/system_programming/src/signals_ping_pong/ex4child.out");
	return 0;	
}
