#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void collatz(int x){
	printf("%d: ", x);
	while (x > 1){
		if(x % 2){
			x = 3 * x + 1;
		}
		else{
			x /= 2;
		}
		printf(" %d", x);
	}
	printf("\n");
}

int main(int argc, char* argv[]){
	int num = argc - 1;
	int* nums = (int*)malloc(num * sizeof(int));
	for(int i = 0; i < num; ++i){
		const char* arg = argv[i + 1];
		if(sscanf(arg, "%d", nums + i) != 1){
			fprintf(stderr, "Unable to convert");
			return 1;	
		}	
	}
	
	printf("Starting parent %d\n", getpid());

	for(int i = 0; i < num; ++i){
		pid_t pid = fork();
		
		if(pid < 0){
			fprintf(stderr, "Failed to fork");
			return -1;
		}
		else if( pid == 0){
			collatz(nums[i]);
			printf("Done parent %d, Me %d\n", getppid(), getpid());
			return 0;
		}
		else{
			wait(NULL);
		}
	}
	printf("Done parent %d, Me %d\n", getppid(), getpid());
	return 0;
}
