#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
int main(int argc, char *argv[])
{
	int		loop;
	char	buff[128];
	struct timeval start, end;

	gettimeofday( &start, NULL );
	printf("start : %ld.%ld\n", start.tv_sec, start.tv_usec);

	int fd = open("test3.txt", O_CREAT | O_WRONLY);
	if(fd < 0) {
		return -1;
	}

	for(loop = 0; loop < 1000; loop++){
		sprintf(buff, "This is Test %d\n", loop);
		write(fd, buff, strlen(buff));
	}
	close(fd);

	gettimeofday( &end, NULL );
	printf("end   : %ld.%ld\n", end.tv_sec, end.tv_usec);

	return 0;
}
