#include <stdio.h>
#include <pthread.h>
#define N 1024
#define N_THREADS 32

int matrix1[N][N];
int matrix2[N][N];
int result[N][N];
void *multiplier(void *arg);

int main(){
    pthread_t threads[N_THREADS];
    int i, j, k;
    for(i = 0; i < N;i++){
        for(j = 0; j < N; j++){
            matrix1[i][j] = i * j;
            matrix2[i][j] = i + j;
        }
    }

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

    return 0;
}


void *multiplier(void *arg){
    int *from_to;
    from_to = (int *)arg;
    for(int i = from_to[0]; i < from_to[1]; i++){
        for(int j =0; j < N; j++){
            result[i][j] = 0;
            for (int k = 0; k < N; k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}
