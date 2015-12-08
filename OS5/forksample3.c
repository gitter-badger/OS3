#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int pid;
	if ((pid = fork()) < 0) {
		perror("fork was failed");
		exit(1);
	}
	if (pid == 0 ) {
		printf("I am a child\n");
		pid = getpid();
		printf("My process id is %d.\n", pid);
		exit(0);
	} else {
		printf("I am the parent.\n");
		// int status;
		// waitpid(pid, &status, 0);
		sleep(100);
		exit(0);
	}
}

