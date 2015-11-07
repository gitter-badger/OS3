#include <unistd.h>
#include <stdlib.h>
void main(int argc, char* arg[]){
	write(1, "Hello, World!\n", 14);
	exit(0);
}
