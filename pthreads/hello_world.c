#include <stdio.h>
#include <pthread.h>

void* func(void *arg){
	printf("Hello, World! Thread Number : %d\n", *((int*)arg));
	return NULL;
}

int main(){
	int i;
	pthread_t tids[2];
	// creating threads
	for(i = 0; i < 2; i ++){
		pthread_create(&tids[i], NULL, func, (void*)(&i));
	}
	for(i = 0; i < 2; i ++){
		pthread_join(tids[i], NULL);
	}
	/*
	pthread_t thread1, thread2;
	// printf("sizeof pthread_t => %lu, sizeof int = %lu, sizeof long unsigned int = %lu\n", sizeof(pthread_t), sizeof(int), sizeof(long unsigned int));
	long unsigned int *tid;
	// thread 1
	
	pthread_create(&thread1, NULL, func, (void*)(&thread1));
	
	// thread 2
	tid = &thread2;
	pthread_create(&thread2, NULL, func, (void*)tid);
	
	// joining both
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	*/
	return 0;
}
