#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

int main(int argc, char **argv)
{
	int sfd, nread;
	char buf[BUF_SIZE];

	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;

	struct addrinfo hints, *res, *rp;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;             
    	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; 
    	hints.ai_flags |= AI_NUMERICSERV;
	hints.ai_protocol = 0;
	hints.ai_addr = NULL;
        hints.ai_next = NULL;             
    	getaddrinfo(NULL, argv[1], &hints, &res);

	for (rp = res; rp != NULL; rp = rp->ai_next) {
               sfd = socket(rp->ai_family, rp->ai_socktype,
                       rp->ai_protocol);
               if (sfd == -1)
                   continue;

               if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   break;                  /* Success */

               close(sfd);
        }

	freeaddrinfo(res);

	while (1) {
		peer_addr_len = sizeof(peer_addr);
		nread = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);

		sendto(sfd, buf, nread, 0,(struct sockaddr *) &peer_addr, peer_addr_len);
	}
}
