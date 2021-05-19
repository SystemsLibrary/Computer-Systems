#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>

#define MAXLINE 50

void gai_error(int code, char *msg) /* Getaddrinfo-style error */
{
    fprintf(stderr, "%s: %s\n", msg, gai_strerror(code));
    exit(0);
}

void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags)
{
    int rc;

    if ((rc = getnameinfo(sa, salen, host, hostlen, serv, 
                          servlen, flags)) != 0) 
        gai_error(rc, "Getnameinfo error");
}

void Freeaddrinfo(struct addrinfo *res)
{
    freeaddrinfo(res);
}

int main(int argc, char **argv)
{
	struct addrinfo *p, *listp, hints;
	char buf[MAXLINE];
 	int rc, flags;

 	/* Get a list of addrinfo records */
 	memset(&hints, 0, sizeof(struct addrinfo));
 	hints.ai_family = AF_INET; /* IPv4 only */
 	hints.ai_socktype = SOCK_STREAM; /* Connections only */
 	
	if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0) {
 		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
 		exit(1);
 	}
 
	/* Walk the list and display each IP address */
 	flags = NI_NUMERICHOST; /* Display address instead of name */
 	
	for (p = listp; p; p = p->ai_next) {
 		Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
 		printf("%s\n", buf);
 	}
 
	/* Clean up */
 	Freeaddrinfo(listp);
 	exit(0);
} 
