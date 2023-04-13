
#include <dirent.h>
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) 
{
    if(argc < 3)
    {
	printf("Invalid command arguments provided!");
	exit(-1);
    }

    DIR* dir = opendir(argv[1]);
    if (dir == NULL) {
        printf("Failed to open directory %s\n", argv[1]);
        exit(-1);
    }

    for(int i = 2; i < argc; ++i)
    {
	char const* filename = argv[i];

	bool isfilefound = false;
	struct dirent* direntry;
	while ((direntry = readdir(dir)) != NULL) 
	{
	    if (strcmp(direntry->d_name, filename) == 0) 
	    {
		isfilefound = true;
		printf("File %s exists\n", filename);
		break;
	    }
	}

	if(isfilefound == false)
	    printf("File %s does not exist\n", filename);
    }

    closedir(dir);
    return 0;
}

