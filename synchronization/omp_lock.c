#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N_THREADS 4

int main(){
	printf("Racing 4 threads against counter variable : Synchronization using openmp\n");
	int counter = 0; // shared variable
	omp_lock_t lock;
    omp_init_lock(&lock);
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
			omp_set_lock(&lock);
            counter += n;
            omp_unset_lock(&lock);
		}
	}
	printf("Actual counter : %d, Expected counter : %d\n", counter, 0);
	return 0;
}
