#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <float.h>
#include <assert.h>
void die (const char *s) {
	perror(s);
	exit(1);
}
#define IN 0
#define OUT 1
int main(int argc, char *argv[]) {
	int pid;
	int c2p[2], p2c[2];
	if (pipe(c2p) < 0 ){
		die("I cannot make a pipe");
	}
	assert (c2p[IN]==3 && c2p[OUT]==4);
	// c2p[IN] for read and c2p[OUT] for write
	if (pipe(p2c) < 0 ){
		die("I cannot make a pipe");
	}
	// assert p2c[0]==5 && p2c[1]==6;
	// p2c[0] for read and fdsFom[1] for write 
	if ((pid = fork()) < 0) {
		die("fork was failed");
	}
	if (pid == 0 ) { // child's side
		if(close(IN) < 0) {
			die ("I cannot close stdin");
		}
		if(dup2(p2c[IN], 0) < 0) {
			die ("I cannot duplicate the pipe");
		}
		if(close(p2c[IN]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		if(close(p2c[OUT]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		//
		if(close(OUT) < 0) {
			die ("I cannot close stdout");
		}
		if(dup2(c2p[OUT], 1) < 0) {
			die ("I cannot duplicate the pipe");
		}
		if(close(c2p[OUT]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		if(close(c2p[IN]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		execl("/usr/bin/bc", "bc", "-lq", NULL);
		die("exec was failed");
	} else { // parent's side
		if(close(c2p[OUT]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		if(close(p2c[IN]) < 0) {
			die ("I cannot close unnecessary pipe");
		}
		// we use c2p[IN] and p2c[OUT] as read and write,
		// respectively.
#define BUFFSIZE 256
#define TRUE 1
		char buf[BUFFSIZE];
		FILE *in = fdopen(c2p[IN],"r");
		FILE *out = fdopen(p2c[OUT], "w");

		/* for bc function definition */
		fprintf(out, "define tan(x) {\n");
		fprintf(out, "return (s(x) / c(x))}\n");
		fprintf(out, "define sin(x) {\n");
		fprintf(out, "return (s(x))}\n");
		fprintf(out, "define cos(x) {\n");
		fprintf(out, "return (c(x))}\n");
		fprintf(out, "define log(x) {\n");
		fprintf(out, "return (l(x))}\n");
		fprintf(out, "define exp(x) {\n");
		fprintf(out, "return (e(x))}\n");
		while (TRUE) {
			if (fgets(buf, BUFFSIZE, stdin) == NULL) {
				exit(1);
			}
			char op[5];
			if (strncmp(buf, "sin", 3) == 0) {
				strncpy(op, buf, 3);
				op[3]='\0'; // force null terminate
			} else if (strncmp(buf, "cos", 3) == 0) {
				strncpy(op, buf, 3);
				op[3]='\0'; // force null terminate
			} else if (strncmp(buf, "tan", 3) == 0) {
				strncpy(op, buf, 3);
				op[3]='\0'; // force null terminate
			} else if (strncmp(buf, "log", 3) == 0) {
				strncpy(op, buf, 3);
				op[3]='\0'; // force null terminate
			} else if (strncmp(buf, "exp", 3) == 0) {
				strncpy(op, buf, 3);
				op[3]='\0'; // force null terminate
			} else {
				break;
			}
			int i;
			for (i = 1; i < 100; i++) {
				double f=((double)i)/100.0 * 3.14159265359;
				fprintf(out, "%s(%f)\n", op, f);
				// fprintf(stdout,"%s(%f)\n", op, f);
				fflush(out);
				fgets(buf, BUFFSIZE, in);
				fprintf(stdout, "%s(%f) = %s", op, f, buf);
			}
		}
		fprintf(out, "quit\n");
		int status;
		waitpid(pid, &status);
		exit(0);
	}
}
