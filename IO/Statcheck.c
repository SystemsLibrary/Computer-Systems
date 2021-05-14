#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <time.h>

//#define st_atime stat.st_atime
//#define st_mtime st_mtime
//#define st_ctime st_ctime

struct stats{
	dev_t st_dev; /* Device */
	ino_t st_ino; /* inode */
	mode_t st_mode; /* Protection and file type */
	nlink_t st_nlink; /* Number of hard links */
	uid_t st_uid; /* User ID of owner */
	gid_t st_gid; /* Group ID of owner */
	dev_t st_rdev; /* Device type (if inode device) */
	off_t st_size; /* Total size, in bytes */
	unsigned long st_blksize; /* Blocksize for filesystem I/O */
	unsigned long st_blocks; /* Number of blocks allocated */
	time_t statime; /* Time of last access */
	time_t stmtime; /* Time of last modification */
	time_t stctime; /* Time of last change */
};



int main (int argc, char **argv)
{
	struct stats stat1;
	char *type, *readok;

	stat(argv[1], &stat1);
	
	if (S_ISREG(stat1.st_mode))
		type = "regular";
	else if (S_ISDIR(stat1.st_mode))
		type = "directory";
	else
		type = "other";

	if ((stat1.st_mode & S_IRUSR)) /* Check read access */
		readok = "yes";
	else
		readok = "no";

	printf("type: %s, read: %s\n", type, readok);
	printf ( "Time of Last Access: %s\n", ctime (&stat1.statime) );
	printf ( "Time of Last Change: %s\n", ctime (&stat1.stctime) );
	exit(0);
}
