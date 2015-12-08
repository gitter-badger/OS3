#include <stdio.h>
#include <setjmp.h>
jmp_buf jmpbuf;
void sub(void) {
	printf("sub start\n");
	printf("do something normal\n");
//	longjmp(jmpbuf, 1); // some error
	printf("sub end\n");
}
int main(int argc, char *argv[]) {
	printf("main start\n");
	int c;
	if ((c = setjmp(jmpbuf)) == 0) {
		// Normal routine
		sub();
	} else {
		// something bad happen
		printf("Error happen. no: %d\n", c);
	}
	printf("main end\n");
}
