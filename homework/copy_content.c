#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("invalid command arguments provided!");
		exit(-1);
	}

	int source_fd = open(argv[1], O_RDONLY);
	if(source_fd < 0)
	{
		printf("%s file doesn't exist\n", argv[1]);
		exit(-1);
	}
	
	int target_fd = creat(argv[2], S_IRUSR | S_IWUSR);
	if(target_fd < 0)
	{
		printf("can't create %s file \n", argv[2]);
		exit(-1);
	}

	char buf[1];
	int readedbytescount = 0;
	while( (readedbytescount = read(source_fd, buf, 1)) > 0 )
	{
		write(target_fd, buf, readedbytescount);
	}
}

