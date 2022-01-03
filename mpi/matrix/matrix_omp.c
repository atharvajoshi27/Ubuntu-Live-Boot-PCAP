#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "matrix.h"

int R[N][N];

void multiply(int from, int to) {
	int i, j, k;
	for (i = from; i < to; i++) {
		for (j = 0; j < N; j++) {
			R[i][j] = 0;
			for (k = 0; k < N; k++) {
				R[i][j] += A[i][k] * B[k][j];
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
	
	int units = N / N_THREADS;
	#pragma omp parallel num_threads(N_THREADS)
	{
		int id = omp_get_thread_num(), from = id * units, to = min(id*units+units, N);
		// printf("Thread %d started. Multiplies from %d to %d\n", id, from, to);
		
		multiply(from, to);
		// printf("Thread %d ended.\n", id);
	}
	printf("Done\n");
	return 0;
}
