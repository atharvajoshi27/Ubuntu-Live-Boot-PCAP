#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int R[N][N];

void multiply() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			R[i][j] = 0;
			for (int k = 0; k < N; k++) {
				R[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

int main(void) {
	printf("Running multiplication serially ....\n");
	multiply();
	printf("Done\n");
	return 0;
}
