#include <stdio.h>
#include <pthread.h>
#include "matrix.h"

int R[N][N];
void *multiplier(void *arg);

int main(int argc, char *argv[]){
	printf("Running multiplication using pthreads ....\n");
    pthread_t threads[N_THREADS];
    int i, j, k;
   

    int units = N / N_THREADS;
    
    int from_to[2];
    
    for (k = 0; k < N_THREADS; k++){
        if(k == N_THREADS -1){
            from_to[0] = k * units;
            from_to[1] = N;
        }
        else{
            from_to[0] = k * units;
            from_to[1] = (k+1) * units;
        }
        pthread_create(&threads[k], NULL, multiplier, (void *)from_to);
    }
    
    for(k = 0; k < N_THREADS; k ++){
        pthread_join(threads[k], NULL);
    }
	printf("Done\n");
    return 0;
}


void *multiplier(void *arg){
    int *from_to;
    from_to = (int *)arg;
    for(int i = from_to[0]; i < from_to[1]; i++){
        for(int j =0; j < N; j++){
            R[i][j] = 0;
            for (int k = 0; k < N; k++){
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
