#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

void unix_error(char *msg) /* Unix-style error */
{
 	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
 	exit(0);
}

void Fork(void)
{
 	pid_t pid;
 	
	if ((pid = fork()) < 0)
 		unix_error("Fork error");
}

int main()
{
 	pid_t pid;
 	
	printf("L0\n");

	Fork();
 	printf("L1\n");

	Fork();
 	printf("Bye\n");
}