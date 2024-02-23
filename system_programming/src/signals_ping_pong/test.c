#define _POSIX_SOURCE 500
#include <stdio.h> /*printf*/
#include <sys/types.h> /*getpid*/
#include <unistd.h> /*getpid*/
#include <sys/wait.h> /*wait*/
#include <signal.h> /*sigaction*/
#include <unistd.h>/*exec*/

static void SIG1Handler();

int main()
{
	struct sigaction parent;
    parent.sa_handler = SIG1Handler;
	sigaction(SIGUSR1, &parent, NULL);
	sleep(20);
	printf("hi i'm the exec process pid: %d\n", getpid());

	kill(getppid(), SIGUSR2);
	
	

	
	return 0;
	
}


static void SIG1Handler()
{
    printf("exec child: recived SIG1 signal\n");
}
