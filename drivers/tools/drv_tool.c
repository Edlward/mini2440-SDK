#include <stdio.h>
#include <unistd.h>          /* open(), ... */
#include <sys/stat.h>
#include <fcntl.h>

#include <getopt.h>

char device_name[32] = "/dev/xxx";


static char *short_options = "hHo:c:";
static struct option long_options[] =
{
	{ "open" , required_argument, NULL,    'o' },
	{ "close", required_argument, NULL,    'c' },
	{ "Help" , no_argument,       NULL,    'h' },
	{ 0,       0,                 0,       0 } 
};


static int g_help_flag;
static int g_version_flag;

static void usage()
{
  fprintf(
      stderr,
      "\nUsage: drv_tool  [Device] [cmd] [data] ...\n\n"
	  "Options:\n"
	  "  -o  --open               open the device \n"
	  "  -c  --close              close the device \n"
      "  -h, --help               help document  \n"
      "Simple example: :\n"
      " drv_tool  %s  -o 1\n\n",device_name);
}

#define MAX_DATA_CDBSZ 8
static unsigned int data[8];

static int dvr_process_cl(int argc, char **argv)
{
	int c;
	while(1)
	{
		c = getopt_long(argc,argv,short_options,long_options,NULL);
		if(-1 == c)
			break;

		switch(c)
		{
			case 'h':
			case 'H':
				g_help_flag = 1;
				return 0;

			case 'v':
				g_version_flag = 1;
				return 0;

			case 'o':
				sscanf(optarg,"%d",&data[0]);
				printf("data : %d \n", data[0]);
				break;

			case 'c':
				sscanf(optarg,"%d",&data[0]);
				printf("data : %d \n", data[0]);
				break;

			default:
				break;
		}
	}

	if(optind >= argc)
	{
	    printf("No device found ! \n");
	    return -1;
	}

	strcpy(device_name, argv[optind]);
	++optind;

	return 0;
}

int main(int argc, char **argv)
{
	int fd ;

	int val = 0;

	int ret ;
	ret = dvr_process_cl(argc , argv);
	if(0 != ret)
	{
		usage();
	    return ret;
	}
	else if(1 == g_help_flag)
	{
		usage();
		return 0;
	}

	fd = open(device_name, O_RDWR);
	if(fd < 0)
	{
		printf("open err ! \n");
		return -1;
	}

	//ssize_t write(int filedes, void *buf, size_t nbytes);
	write(fd, data, 8);   // here should be 4
	
	close(fd);
	return 0;
}

