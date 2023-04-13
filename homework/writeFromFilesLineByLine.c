
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main(int argc, char** argv) {
    if(argc != 3)
    {
	printf("invalid command arguments provided!");
	exit(-1);
    }

    int source1_fd = open(argv[1], O_RDONLY);
    if (source1_fd < 0) {
        printf("%s file doesn't exist\n", argv[1]);
        exit(EXIT_FAILURE);
    }
	
    int source2_fd = open(argv[2], O_RDONLY);
    if(source2_fd < 0)
    {
	printf("%s file doesn't exist\n", argv[2]);
	exit(EXIT_FAILURE);
    }

    int target_fd = creat("output.txt", S_IRUSR | S_IWUSR);
    if(target_fd < 0)
    {
	printf("can't create output.txt file \n");
	exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int readed_bytes_fd1 = 0;
    int readed_bytes_fd2 = 0;
 
    int i;
    
    int readed1 = 0;
    int readed2 = 0;

    do
    {
	i = 0;
	int readed = 0;
	do {
            readed_bytes_fd1 = read(source1_fd, &buffer[i], 1);
            if (readed_bytes_fd1 <= 0) {
                break;
            }
            i++;
	    readed += readed_bytes_fd1;
    	} while (readed_bytes_fd1 > 0 && buffer[i - 1] != '\n' && i < BUFFER_SIZE);

	readed1 = i;
	write(target_fd, buffer, readed);
	
	i = 0;
	readed = 0;
	do {
            readed_bytes_fd2 = read(source2_fd, &buffer[i], 1);
            if (readed_bytes_fd2 <= 0) {
                break;
            }
            i++;
	    readed += readed_bytes_fd2;
    	} while (readed_bytes_fd2 > 0 && buffer[i - 1] != '\n' && i < BUFFER_SIZE);

	readed2 = i;
	write(target_fd, buffer, readed);

    }
    while(readed1 > 0 || readed2 > 0);

    if (close(source1_fd) == -1 || close(source2_fd) == -1 || close(target_fd) ) {
        perror("close() error");
        exit(EXIT_FAILURE);
    }

    return 0;
}


