#include <stdio.h>
#include <stdlib.h>

#define N 1024

int matrix1[N][N];
int matrix2[N][N];
int result[N][N];

void multiply() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			result[i][j] = 0;
			for (int k = 0; k < N; k++) {
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}

int main(void) {
	int i, j;
	for(i = 0; i < N; i ++){
		for(j = 0;  j < N; j ++){
			matrix1[i][j] = rand();
			matrix2[i][j] = rand();
		}
	}
	multiply();
	return 0;
}
