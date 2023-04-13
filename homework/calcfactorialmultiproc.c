
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROCESS_COUNT 3

int get_multiplied(int _start, int _end){
	int result = 1;


	for(size_t i = _start; i < _end; ++i){
		result *= i;	
	}
	return result;
}

int main(){
	int number = 5;
	int pipefd[PROCESS_COUNT][2];
	int block_size = number % PROCESS_COUNT != 0 ? number/PROCESS_COUNT + 1 : number/PROCESS_COUNT;
	pid_t child_pid;

	for(size_t i = 0; i < PROCESS_COUNT; ++i){
		pipe(pipefd[i]);
		child_pid = fork();
		if(child_pid == 0){
			int multiplied = 0;
			int start_index = i * block_size + 1;
			int end_index = start_index + block_size;
			if(end_index > number){
				end_index = number + 1;
			}
			multiplied = get_multiplied(start_index, end_index);
			write(pipefd[i][1], &multiplied, sizeof(multiplied));
			close(pipefd[i][1]);
			exit(0);
		}
	}
	
	int total_factorial = 1;
	for(size_t i = 0; i < PROCESS_COUNT; ++i){
		wait(NULL);
		int local_multiply_res;
		read(pipefd[i][0], &local_multiply_res, sizeof(local_multiply_res));
		total_factorial *= local_multiply_res;
		close(pipefd[i][0]);
	}
	printf("TOTAL FACTORIAL: %i\n", total_factorial);

	return 0;
}
