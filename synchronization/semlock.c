#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

long long int counter = 0;
sem_t mutex;

void *inc1(void *arg){
    for(int i=0; i < 50000; i++){
        sem_wait(&mutex);
        counter += 1;
        sem_post(&mutex);
    }
    pthread_exit(NULL);
}

void *inc2(void *arg){
    for(int i = 0; i < 50000; i++){
    	sem_wait(&mutex);
    	counter += 2;
    	sem_post(&mutex);
    }
    pthread_exit(NULL);
}

void *dec2(void *arg){
    for(int i = 0; i < 50000; i++){
    	sem_wait(&mutex);
    	counter -= 2;
    	sem_post(&mutex);
    }
       
    pthread_exit(NULL);
}

void *dec1(void *arg){
    for(int i = 0; i < 50000; i++){
    	sem_wait(&mutex);
    	counter -= 1;
    	sem_post(&mutex);
    }
    pthread_exit(NULL);
}

int main(){
    printf("Racing 4 threads against counter variable : Synchronization using semaphores\n");
    sem_init(&mutex, 0, 1); 
    pthread_t threads[4];

    pthread_create(&threads[0], NULL, inc1, NULL);
    pthread_create(&threads[1], NULL, inc2, NULL);
    pthread_create(&threads[2], NULL, dec2, NULL);
    pthread_create(&threads[3], NULL, dec1, NULL);

    //joining 4 threads

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);

    printf("Exptected counter value : 0\n");
    printf("Actual counter value : %lld\n", counter);

    return 0;
}
