// test for first_drv
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	int fd ;

	int val = 1;
	fd = open("/dev/xxx", O_RDWR);

	if(fd < 0)
	{
		printf("open err ! \n");
	}

	write(fd, &val , 1);
	
	return 0;
}
