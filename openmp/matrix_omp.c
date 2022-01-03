#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1024
#define N_THREADS 8

int matrix1[N][N];
int matrix2[N][N];
int result[N][N];

void multiply(int from, int to) {
	int i, j, k;
	for (i = from; i < to; i++) {
		for (j = 0; j < N; j++) {
			result[i][j] = 0;
			for (k = 0; k < N; k++) {
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}

int min(int a, int b){
	return a < b ? a : b;
}

int main(void) {
	printf("Running matrix multiplication with %d threads using OpenMP\n", N_THREADS);
	int i, j;
	for(i = 0; i < N; i ++){
		for(j = 0;  j < N; j ++){
			matrix1[i][j] = rand();
			matrix2[i][j] = rand();
		}
	}
	
	int units = N / N_THREADS;
	#pragma omp parallel num_threads(N_THREADS)
	{
		int id = omp_get_thread_num(), from = id * units, to = min(id*units+units, N);
		// printf("Thread %d started. Multiplies from %d to %d\n", id, from, to);
		
		multiply(from, to);
		// printf("Thread %d ended.\n", id);
	}
	
	return 0;
}
