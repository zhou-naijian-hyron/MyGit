/*
 * fprint_test.c
 *
 *  Created on: 2016/11/16
 *      Author: mcc
 */

#include <stdio.h>
#include <sys/time.h>
int main(int argc, char *argv[])
{
	int		loop;
	struct timeval start, end;

	gettimeofday( &start, NULL );
	printf("start : %ld.%ld\n", start.tv_sec, start.tv_usec);

	FILE *fp = fopen("test1.txt", "a");
	if(!fp){
		return -1;
	}

	for(loop = 0; loop < 1000; loop++){
		fprintf(fp, "This is Test %d\n", loop);
	}
	fclose(fp);

	gettimeofday( &end, NULL );
	printf("end   : %ld.%ld\n", end.tv_sec, end.tv_usec);
	
	return 0;
}

