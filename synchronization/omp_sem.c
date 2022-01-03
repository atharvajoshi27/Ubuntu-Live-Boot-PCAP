#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <omp.h>

#define N_THREADS 4

int main(){
	printf("Racing 4 threads against counter variable : Synchronization using openmp (semaphore)\n");
	int counter = 0; // shared variable
	sem_t lock;
    sem_init(&lock, 0, 1);
    
	#pragma omp parallel shared(counter) num_threads(N_THREADS) 
	{
		int id = omp_get_thread_num(), i, n;
		switch(id){
			case 0 :
				n = 1;
				break;
			case 1 :
				n = 2;
				break;
			case 2 :
				n = -1;
				break;
			case 3 : 
				n = -2;
				break;
			default :
				printf("Wrong no. of threads. Exiting.");
				exit(1);
				break;
		}
		for(i = 0; i < 50000; i ++){
			sem_wait(&lock);
            counter += n;
            sem_post(&lock);
		}
	}
	printf("Actual counter : %d, Expected counter : %d\n", counter, 0);
	return 0;
}
