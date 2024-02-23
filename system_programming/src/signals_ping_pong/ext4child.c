#define _POSIX_SOURCE 500
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 


void new_handler(int signum)
{
	char *print = "Recived SIGUSR1\n";
	size_t len = strlen(print);   
	write(STDOUT_FILENO, print, len);     
}


int main(int argc, char *argv[], char *envp[])
{
	struct sigaction sa;
	int i = 0;
	pid_t pid = -2;
	sa.sa_handler = &new_handler;
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
	{
		perror("sigaction");
	}

	if (argv[1])
	{
		pid = atoi(argv[1]);
		printf("%d\n", pid);
		for (i = 0; i < 5; ++i)
		{
			sleep(1);
			kill(pid, SIGUSR2);
			pause();
		}

	}
	else
	{
		for (i = 0; i < 5; ++i)
		{
			pause();
			kill(getppid(), SIGUSR2);
		}
	}
	return 0;
}
