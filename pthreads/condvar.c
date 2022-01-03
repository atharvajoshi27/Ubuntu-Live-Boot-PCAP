#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

long long int counter = 0;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int working = 0;
void *inc1(void *arg){
    for(int i=0; i < 50000; i++){
		while(1){
		    pthread_mutex_lock(&lock);
		    if(working == 0){ // we can work
		    	working = 1;
		    	counter += 1;
		    	working = 0;
		    	pthread_cond_signal(&cond);
		    	pthread_mutex_unlock(&lock);
		    	break;
		    }
		    pthread_cond_wait(&cond, &lock);
		    pthread_mutex_unlock(&lock);
		}
    }
    pthread_exit(NULL);
}

void *inc2(void *arg){
    for(int i = 0; i < 50000; i++){
    	while(1){
		    pthread_mutex_lock(&lock);
		    if(working == 0){ // we can work
		    	working = 1;
		    	counter += 2;
		    	working = 0;
		    	pthread_cond_signal(&cond);
		    	pthread_mutex_unlock(&lock);
		    	break;
		    }
		    pthread_cond_wait(&cond, &lock);
		    pthread_mutex_unlock(&lock);
		}
    }
    pthread_exit(NULL);
}

void *dec2(void *arg){
    for(int i = 0; i < 50000; i++){
    	while(1){
		    pthread_mutex_lock(&lock);
		    if(working == 0){ // we can work
		    	working = 1;
		    	counter -= 2;
		    	working = 0;
		    	pthread_cond_signal(&cond);
		    	pthread_mutex_unlock(&lock);
		    	break;
		    }
		    pthread_cond_wait(&cond, &lock);
		    pthread_mutex_unlock(&lock);
		}
    }
       
    pthread_exit(NULL);
}

void *dec1(void *arg){
    for(int i = 0; i < 50000; i++){
    	while(1){
		    pthread_mutex_lock(&lock);
		    if(working == 0){ // we can work
		    	working = 1;
		    	counter -= 1;
		    	working = 0;
		    	pthread_cond_signal(&cond);
		    	pthread_mutex_unlock(&lock);
		    	break;
		    }
		    pthread_cond_wait(&cond, &lock);
		    pthread_mutex_unlock(&lock);
		}
    }
    pthread_exit(NULL);
}

int main(){
    printf("Racing 4 threads against counter variable : Synchronization using condition variable\n");
 
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
