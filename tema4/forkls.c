#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t pid = getpid();
	
	pid_t cpid = fork();
	int a;
	if(cpid < 0){
		fprintf(stderr, "Failed to fork process\n");
		return -1;
	}
	else if(cpid == 0){
		char path[] = "/bin/ls";
		char* argv[] = {path, NULL};
		char* envp[] = {NULL};
		a = execve(path, argv, envp);
		printf("%d", a);
	}
	else{
		wait(NULL);
		printf("Parent PID = %d, Child PID = %d\n", pid, cpid);
		return 0;
	}
}
