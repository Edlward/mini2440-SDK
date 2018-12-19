#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	int fd;
	int val = 1;	

	if(argc != 2)
	{
		printf("please check the argc . \n");
		printf("usage : leddrv_test [status] (status = 1, on; 0, off)  \n");
		return -1;
	}

	if(strcmp(argv[1], "on") == 0)
	{
		printf("val : %d \n", val);
		val = 1;
	}
	else
	{
		val = 0;
	}

	fd = open("/dev/myled", O_RDWR);
	if(fd < 0)
	{
		printf("open error ! \n");
		return -1;
	}

	write(fd, &val, 4);

	close(fd);
	return 0;
}


