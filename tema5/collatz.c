#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
	
	shm_unlink("c_shm");
	int shm_fd = shm_open("c_shm", O_RDWR | O_CREAT | O_EXCL, S_IRWXU);
	if(shm_fd < 0){
		perror(NULL);
		return -1;
	}
	
	const size_t ps = getpagesize();

	if(ftruncate(shm_fd, num * ps) !=0){
		perror(NULL);
		shm_unlink("c_shm");
		return -1;
	}

	printf("Starting parent %d\n", getpid());

	int* results = mmap(NULL, num * ps, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(results == MAP_FAILED){
		perror(NULL);
		shm_unlink("c_shm");
		return -1;
	}
	

	for(int i = 0; i < num; ++i){
		pid_t pid = fork();
		
		if(pid < 0){
			fprintf(stderr, "Failed to fork");
			return -1;
		}
		else if( pid == 0){
			int* res_child = mmap(NULL, ps, PROT_WRITE, MAP_SHARED, shm_fd, i*ps);
			
			if(res_child == MAP_FAILED){
				perror(NULL);
				shm_unlink("c_shm");
				return -1;
			}
		
			int v = nums[i];
			int len = 0;

			res_child[len++] = v;
			
			while (v > 1){
				if(v % 2){
					v = 3 * v + 1;
				}
				else{
					v /= 2;
				}
				res_child[len++] = v;
			}

			munmap(res_child, ps);

			printf("Done parent %d, Me %d\n", getppid(), getpid());
			return 0;
		}
	}

	for(int i = 0; i < num; ++i){
		wait(NULL);
	}
	
	for(int i = 0; i < num; ++i){
		int v = results[(i*ps)/4];
		int len = 1;
		printf("%d ", v);
		while(v!=1){
			v = results[(i*ps)/4+len];
			len++;
			printf("%d ", v);
		}
		printf("\n");	
	}

	shm_unlink("c_shm");
	munmap(results, num*ps);

	printf("Done parent %d, Me %d\n", getppid(), getpid());
	return 0;
}
