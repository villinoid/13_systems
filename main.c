#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static void sighandler(int signo) {
	if ( signo == SIGUSR1 ){
		printf("ppid: %d\n",getppid());
	}
	if(signo == SIGINT){
		int file = open ("log", O_WRONLY | O_APPEND | O_CREAT, 0644);
		char message[]="Program exited to receiving SIGINT\n";
		write(file, message, strlen(message));
		exit(0);
	}
}

int main() {
	signal(SIGUSR1,sighandler);
	signal(SIGINT,sighandler);
	while (1){
		printf("pid: %d\n",getpid());
		sleep(1);
	}
	return 0;
}