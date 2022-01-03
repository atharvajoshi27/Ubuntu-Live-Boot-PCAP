#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 1024
#define N_THREADS 8

int matrix1[N][N];
int matrix2[N][N];
int result[N][N];

void *multiply(void *arg){
    int i, j, k, from = ((int*)arg)[0], to = ((int*)arg)[1];
    for(i = from; i < to; i ++){
        for(j = 0; j < N; j ++){
            result[i][j] = 0;
            for (k = 0; k < N; k ++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int min(int a, int b){
	return a < b ? a : b;
}

int main(){
    pthread_t threads[N_THREADS];
    int i, j, k;
    for(i = 0; i < N;i++){
        for(j = 0; j < N; j++){
            matrix1[i][j] = rand();
            matrix2[i][j] = rand();
        }
    }

    int units = N / N_THREADS;
    
    int from_to[2];
    
    for (k = 0; k < N_THREADS; k++){
        
        from_to[0] = k * units;
        from_to[1] = min(from_to[0]+units, N);
        
        pthread_create(&threads[k], NULL, multiply, (void *)from_to);
    }
    
    for(k = 0; k < N_THREADS; k ++){
        pthread_join(threads[k], NULL);
    }


    return 0;
}
