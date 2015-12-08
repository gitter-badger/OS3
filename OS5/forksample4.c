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
		printf("(c)I am a child.\n");
		printf("(c)I will be ls command!\n");
		execl("/bin/ls", "ls", "-la", NULL);
		perror("exec was failed");
		exit(1);
	} else {
		printf("(p)I am the parent.\n");
		printf("(p)I will sleep a while.\n");
		int status;
		waitpid(pid, &status, 0);
		sleep(10);
		printf("(p)I will terminate myself.\n");
		exit(0);
	}
}

