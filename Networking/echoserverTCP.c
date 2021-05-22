#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024
#define RIO_BUFSIZE 8192
#define LISTENQ  1024

typedef struct {
    int rio_fd;                /* Descriptor for this internal buf */
    int rio_cnt;               /* Unread bytes in internal buf */
    char *rio_bufptr;          /* Next unread byte in internal buf */
    char rio_buf[RIO_BUFSIZE]; /* Internal buffer */
} rio_t;

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;

    while (rp->rio_cnt <= 0) {  /* Refill if buf is empty */
	rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, 
			   sizeof(rp->rio_buf));
	if (rp->rio_cnt < 0) {
	    if (errno != EINTR) /* Interrupted by sig handler return */
		return -1;
	}
	else if (rp->rio_cnt == 0)  /* EOF */
	    return 0;
	else 
	    rp->rio_bufptr = rp->rio_buf; /* Reset buffer ptr */
    }

    /* Copy min(n, rp->rio_cnt) bytes from internal buf to user buf */
    cnt = n;          
    if (rp->rio_cnt < n)   
	cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) 
{
    int n, rc;
    char c, *bufp = usrbuf;

    for (n = 1; n < maxlen; n++) { 
        if ((rc = rio_read(rp, &c, 1)) == 1) {
	    *bufp++ = c;
	    if (c == '\n') {
                n++;
     		break;
            }
	} else if (rc == 0) {
	    if (n == 1)
		return 0; /* EOF, no data read */
	    else
		break;    /* EOF, some data was read */
	} else
	    return -1;	  /* Error */
    }
    *bufp = 0;
    return n-1;
}

void rio_readinitb(rio_t *rp, int fd) 
{
    rp->rio_fd = fd;  
    rp->rio_cnt = 0;  
    rp->rio_bufptr = rp->rio_buf;
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n) 
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while (nleft > 0) {
	if ((nwritten = write(fd, bufp, nleft)) <= 0) {
	    if (errno == EINTR)  /* Interrupted by sig handler return */
		nwritten = 0;    /* and call write() again */
	    else
		return -1;       /* errno set by write() */
	}
	nleft -= nwritten;
	bufp += nwritten;
    }
    return n;
}

int main(int argc, char **argv)
{
	int sfd, nread;
	char buf[BUF_SIZE];
	rio_t rio;

	size_t n;
	int optval = 1;

	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;

	struct addrinfo hints, *res, *rp;

	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;             
    	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; 
    	hints.ai_flags |= AI_NUMERICSERV;          
    	getaddrinfo(NULL, argv[1], &hints, &res);

	for (rp = res; rp != NULL; rp = rp->ai_next) {
               sfd = socket(rp->ai_family, rp->ai_socktype,
                       rp->ai_protocol);
               if (sfd == -1)
                   continue;
		
	       setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(int));

               if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   break;                  /* Success */

               close(sfd);
        }

	freeaddrinfo(res);
	
	listen(sfd, LISTENQ);

	while (1) {
		peer_addr_len = sizeof(peer_addr);

		nread = accept(sfd, (struct sockaddr *)&peer_addr, &peer_addr_len);
		
		rio_readinitb(&rio, nread);

		n = rio_readlineb(&rio, buf, BUF_SIZE);

		rio_writen(sfd, buf, n);

		close(sfd);
	}
}
