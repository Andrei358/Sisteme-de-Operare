#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void* reverse_string(void* input){
	char *st = input;

	size_t stl = strlen(st);

	char *ost = malloc(sizeof(char) * (stl+1));

	for(size_t i = 0; i < stl; ++i){
		ost[i] = st[stl - i - 1];
	}

	ost[stl]='\0';
	
	return ost;
}

int main(int argc, char* argv[]){
	char *st = argv[1];

	pthread_t worker_id;

	if(pthread_create(&worker_id, NULL, reverse_string, st)){
		perror(NULL);
		return -1;
	}	

	char* res = NULL;
	pthread_join(worker_id, (void**) &res);

	printf("Reversed: %s\n", res);

	free(res);

	return 0;
}
