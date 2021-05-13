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

pid_t Fork(void)
{
 	pid_t pid;
 	
	if ((pid = fork()) < 0)
 		unix_error("Fork error");
	
	return pid;
}

int main()
{
 	printf("L0\n");
 	
	if (Fork() == 0) {
 		printf("L1\n");
 		
		if (Fork() == 0) {
 			printf("L2\n");
 		}
 	}
 
	printf("Bye\n");
}