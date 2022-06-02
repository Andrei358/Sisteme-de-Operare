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
	pid_t pid = fork();
	
	if(pid < 0){
		fprintf(stderr, "Failed to fork");
		return -1;
	}
	else if( pid == 0){
		char *p;
		collatz(strtol(argv[1], p, 10));
		return 0;
	}
	else{
		wait(NULL);
		printf("Child process %d finished\n", pid);
		return 0;
	}
}
