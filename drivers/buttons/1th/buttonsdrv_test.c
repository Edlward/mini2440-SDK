/* 
 *   buttons驱动测试 ： 采用轮询的方式
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	int fd ;

	unsigned char key_values[6];
	int cnt = 0;

	fd = open("/dev/buttons", O_RDWR);
	if(fd < 0)
	{
		printf("open err ! \n");
		return -1;
	}

	while(1)
	{
		read(fd, key_values, sizeof(key_values));
		if((!key_values[0]) || (!key_values[1]) || (!key_values[2]) || (!key_values[3]) || (!key_values[4]) || (!key_values[5]) )
			{
				printf("%04d key pressed : %d %d %d %d %d %d", cnt++, key_values[0],
					key_values[1],key_values[2], key_values[3],
					key_values[4], key_values[5]);
			}
	}
	
	return 0;
}
