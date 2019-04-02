#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int thread_num = 0;

void* func() {
	fprintf(stderr, "thread num %d\n", thread_num);
	pthread_t pid1, pid2;
	if(pthread_create(&pid1, NULL, func, NULL) == 0) thread_num++;
	if(pthread_create(&pid2, NULL, func, NULL) == 0) thread_num++;

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
}

int main() {
	printf("pthread\n");
	pthread_t tid;
	pthread_create(&tid, NULL, func, NULL);
	pthread_join(tid, NULL);
	return 0;
}

