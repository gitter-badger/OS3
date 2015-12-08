#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t trap_signal(int sig, sighandler_t handler) {
	struct sigaction act, old;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	if (sigaction(sig, &act, &old) < 0)
		return NULL;
	return old.sa_handler;
}
void
signalHandlerForAlarm(int sig) {
	alarm(5);
	puts("I catch a signal.");
	if (sig == SIGALRM)
		puts("5 sec. elapsed");
}
#define TRUE 1
int
main(int argc, char *argv[]) {
	trap_signal(SIGALRM, signalHandlerForAlarm);
	alarm(5);
	int i=0;
	while(TRUE) {
		sleep(1);
		fprintf(stdout, "%d-th loop\n", i++);
	}
	exit(0);
}

