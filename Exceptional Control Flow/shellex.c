#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define MAXLINE 1000
#define MAXARGS 128
#define MAXJOBS 50

typedef void handler_t(int);
sigset_t mask_all, mask_one, prev_one;

struct job_t {              /* The job struct */
    pid_t pid;              /* job PID */
};
struct job_t jobs[MAXJOBS];

void unix_error(char *msg) /* Unix-style error */
{
 fprintf(stderr, "%s: %s\n", msg, strerror(errno));
 exit(0);
}

void clearjob(struct job_t *job) {
    job->pid = 0;
}

void initjobs() {
    int i;

    for (i = 0; i < MAXJOBS; i++)
    	clearjob(&jobs[i]);
}

int addjob(pid_t pid) 
{
    int i;
    
    if (pid < 1)
    	return 0;

    for (i = 0; i < MAXJOBS; i++) {
    	if (jobs[i].pid == 0) {
        	jobs[i].pid = pid;
        	
            	return 1;
    	}
    }

    return 0;
}

int deletejob(pid_t pid) 
{
    int i;

    if (pid < 1)
    	return 0;

    for (i = 0; i < MAXJOBS; i++) {
    	if (jobs[i].pid == pid) {
        	clearjob(&jobs[i]);
        	return 1;
    	}
    }
    return 0;
}

handler_t *Signal(int signum, handler_t *handler)
{
 	struct sigaction action, old_action;
 	
	action.sa_handler = handler;
 	sigemptyset(&action.sa_mask); /* Block sigs of type being handled */
 	action.sa_flags = SA_RESTART; /* Restart syscalls if possible */
 	
	if (sigaction(signum, &action, &old_action) < 0)
 		unix_error("Signal error");
	return (old_action.sa_handler);
}

static size_t sio_strlen(char s[])
{
    int i = 0;

    while (s[i] != '\0')
        ++i;
    return i;
}

ssize_t sio_puts(char s[]) /* Put string */
{
    return write(STDOUT_FILENO, s, sio_strlen(s)); //line:csapp:siostrlen
}

void sio_error(char s[]) /* Put error message and exit */
{
    sio_puts(s);
    _exit(1);                                      //line:csapp:sioexit
}

void handler(int sig)
{
 	int olderrno = errno;
 	sigset_t mask_all, prev_all;
 	pid_t pid;
 	
	sigfillset(&mask_all);
 	while ((pid = waitpid(-1, NULL, 0)) > 0) 
	{ /* Reap child */
 		sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
 		deletejob(pid); /* Delete the child from the job list */
 		sigprocmask(SIG_SETMASK, &prev_all, NULL);
 	}

 	if (errno != ECHILD)
 		sio_error("waitpid error");
 	errno = olderrno;
}

int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit")) /* quit command */
	exit(0);  
    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
	return 1;
    return 0;                     /* Not a builtin command */
}

int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
	       buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}

void eval(char *cmdline)
{
 	char *argv[MAXARGS]; /* Argument list execve() */ 
	char buf[MAXLINE]; /* Holds modified command line */ 
	int bg; /* Should the job run in bg or fg? */
 
	pid_t pid; /* Process id */

 	strcpy(buf, cmdline);
 	bg = parseline(buf, argv); 
	
	if (argv[0] == NULL) 
		return; /* Ignore empty lines */
	
 	if (!builtin_command(argv))
	{
		sigprocmask(SIG_BLOCK, &mask_one, &prev_one);		
		if ((pid = fork()) == 0) 
		{ /* Child runs user job */
			sigprocmask(SIG_SETMASK, &prev_one, NULL);  
			if (execve(argv[0], argv, NULL) < 0)
			{ 
				printf("%s: Command not found.\n", argv[0]);
 				exit(0);
 			}
 		}
		
		while (!pid)
 			sigsuspend(&prev_one); 

		sigprocmask(SIG_BLOCK, &mask_all, NULL);
		addjob(pid);
		sigprocmask(SIG_SETMASK, &prev_one, NULL);  

 		/* Parent waits for foreground job to terminate */
		if (!bg) { 
			int status;
 
			if (waitpid(pid, &status, 0) < 0) 
				unix_error("waitfg: waitpid error");
 		}
		else 
			printf("%d %s", pid, cmdline);
 	}	

 	return;
}

int main()
{
	char cmdline[MAXLINE]; /* command line */
	
 	sigfillset(&mask_all);
 	sigemptyset(&mask_one);
 	sigaddset(&mask_one, SIGCHLD);
 	signal(SIGCHLD, handler);
 	initjobs(); 
 	
	while (1) {
		/* read */
 		printf("> ");
 		fgets(cmdline, MAXLINE, stdin);
 		
		if (feof(stdin))
 			exit(0);
 
		/* evaluate */
 		eval(cmdline);
 	}
}
