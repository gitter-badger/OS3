#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void die (const char *s) {
	perror(s);
	exit(1);
}
int main(int argc, char *argv[]) {
	int pid;
	int fds[2];
	if (argc < 2) {
		fprintf(stderr, "usage: %s command\n", argv[0]);
		exit(1);
	}
	if (pipe(fds) < 0 ){
		die("I cannot make a pipe");
	}
	 // assert fds[0]==3 && fds[1]==4;
	 //  // fds[0] for read and fds[1] for write 
	if ((pid = fork()) < 0) {
		die("fork was failed");
	}
	if (pid == 0 ) { // child's side
		if(close(0) < 0) {
			die ("I cannot close stdin");
		}
		if(dup2(fds[0], 0) < 0) {
			die ("I cannot duplicate the pipe");
		}
		if(close(fds[0]) < 0) {
			die ("I cannot close unnecessary pipe"); 
		}
		if(close(fds[1]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		execl("/bin/grep", "grep", argv[1], NULL);
		die("exec was failed");
	} else { // parent's side
		if(close(1) < 0) {
			die ("I cannot close stdout");
		}
		if(dup2(fds[1], 1) < 0) {
			die ("I cannot duplicate the pipe");
		}
		if(close(fds[0]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		if(close(fds[1]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		execl("/bin/ps", "ps", "a", NULL);
		die("exec was failed");
	}
}
