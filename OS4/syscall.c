#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
static void do_cat(const char *path);
int main(int argc, char *argv[]) {
	int i;
	for (i=1; i < argc; i++) {
		do_cat(argv[i]);
	}
	exit(0);
}
#define BUFFER_SIZE 20148
#define TRUE 1

static void die(const char* path){
	perror(path);
	exit(1);
}

static void do_cat(const char* path) {
	int fd;
	unsigned char buf[BUFFER_SIZE];
	int n;
	fd = open(path, O_RDONLY);
	if (fd < 0) die(path);
	while(TRUE) {
		n=read(fd, buf, sizeof buf);
		if (n < 0) die(path);
		if (n == 0) break;
		if (write(STDOUT_FILENO, buf, n) < 0) die(path);
	}
	if (close(fd) < 0) die(path);
}
