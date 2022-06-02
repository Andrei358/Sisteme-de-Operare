#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

int** alloc_mat(int r, int c){
	int **data = malloc(sizeof(int*) * r);

	for(int i = 0; i < r; ++i){
		data[i] = malloc(sizeof(int) * c);
	}

	return data;
}

void read_mat(int** mat, int r, int c, FILE* fin){
	for(int i = 0; i < r; ++i){
		for(int j = 0; j < c; ++j){
			fscanf(fin, "%d", &mat[i][j]);
		}
	}
}

void free_matrix(int*** mat, int r){
	for(int i = 0; i < r; ++i){
		free(*mat[i]);
	}

	free(*mat);

	mat = NULL;
}

void* reverse_string(void* input){
	char *st = input;

	size_t stl = strlen(st);

	char *ost = malloc(sizeof(char) * (stl+1));

	int* res = calloc(sizeof(int), 1);

	for(int i = 0; i < ; ++i){
		*res += m1[r][i] * m2[i][c];
	}
	
	return res;
}

int main(int argc, char* argv[]){
	int d1, d2, d3;
	int** mat1, mat2, mat3;

	FILE* fin = fopen("matmul.txt", "rt");
	if(!fin){
		perror(NULL);
		return -1;
	}

	fscanf(fin, "%d %d %d", &d1, &d2, &d3);

	mat1 = alloc_mat(d1, d2);
	read_mat(mat1, d1, d2, fin);
	
	mat2 = alloc_mat(d2, d3);
	read_mat(mat2, d2, d3, fin);
	
	fclose(fin);

	mat3 = alloc_mat(d1, d3);

	int nt = d1 * d3;
	pthread_t* worker_ids = malloc(sizeof(pthread_t) * nt);
	
	int*** inputs = malloc(sizeof(int**)*2);
	inputs[0] = m1;
	inputs[1] = m2;

	for(int i = 0; i < d1; ++i){
		for(int j = 0; j < d3; ++j){
			if(pthread_create(&worker_id[i * d2 + j], NULL, mult_thread, inputs)){
				perror(NULL);
				return -1;
			}	
		}
	}

	char* res = NULL;
	pthread_join(worker_id, (void**) &res);

	printf("Reversed: %s\n", res);

	free(res);

	return 0;
}
