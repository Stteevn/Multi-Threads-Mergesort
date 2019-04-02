#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#define maxn 10000010
#define THREAD_NUM 8
// #define NO_THREAD
#define THREAD
#define DEBUG

int A[maxn];
int temp[maxn];
int n;

int thread_num = 0;

struct atom {
	int l, r;
};

int cmp(const void *lhs, const void *rhs);

long get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void merge(int l, int r) {
	int mid = (l + r) >> 1;
	//int *first = (int *)malloc(sizeof(int) * (unsigned)(mid - l + 1));
	//int *second = (int *)malloc(sizeof(int) * (unsigned)(r - mid + 1));
/*	
	if(first == NULL || second == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(-1);
	}
*/	
	//for(int i = l; i < mid; i++) first[i - l] = A[i];
	//for(int i = mid; i < r; i++) second[i - mid] = A[i];
	//for(int i = l; i < r; i++) temp[i] = A[i];
    memcpy(temp + l, A + l, sizeof(int) * (r - l));
    int i = l, j = mid, k = l;
	while(i < mid && j < r) {
		if(temp[i] < temp[j]) A[k++] = temp[i++];
		else A[k++] = temp[j++];
	}
	while(i < mid) A[k++] = temp[i++];
	while(j < r) A[k++] = temp[j++];

	//free(first);
	//free(second);
}

void* my_merge_sort(void *node) {
	struct atom* p = (struct atom*)node;
	int l = p->l, r = p->r;
#ifdef DEBUG	
	// fprintf(stderr, "%d %d\n", l, r);
	// fprintf(stderr, "thread num %d\n", thread_num);
#endif
    if(r - l <= 5) {
        qsort(A + l, r - l, sizeof(int), cmp);
        return NULL;
    }
    if(r - l <= 1) return NULL;

	int mid = (l + r) >> 1;
	
	struct atom left, right;
	left.l = l;
	left.r = mid;
	right.l = mid;
	right.r = r;
	
#ifdef NO_THREAD
	my_merge_sort((void *)&left);
	my_merge_sort((void *)&right);
#endif
	
#ifdef THREAD
	if((n / (r - l) * 4 >= THREAD_NUM)) {
		my_merge_sort((void *)&left);
        my_merge_sort((void *)&right);
    } else {
        pthread_t tid1, tid2;
        if(pthread_create(&tid1, NULL, my_merge_sort, ((void*)(&left))) != 0) {
            fprintf(stderr, "thread create error\n");
            perror("");
            // exit(-1);
        } else {
            thread_num++;
        }
        if(pthread_create(&tid2, NULL, my_merge_sort, ((void*)(&right))) != 0) {
            //fprintf(stderr, "thread create error\n");
            //perror("");
            // exit(-1);
        }else {
            thread_num++;
        }
	    pthread_join(tid1, NULL);
	    pthread_join(tid2, NULL);
    }
#endif
	merge(l, r);
    return NULL;
}

int cmp(const void *lhs, const void *rhs) {
	return *(int *)lhs - *(int *)rhs;
}

int check(int arr[], int size) {
	int *brr = (int *)malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++) brr[i] = arr[i];
    qsort(brr, size, sizeof(int), cmp);
	for(int i = 0; i < size; i++) {
		if(arr[i] != brr[i]) return 0;
	}
	return 1;
}

void test(int A[], int size) {
	srand(time(NULL));
	n = size;
	for(int i = 0; i < size; i++) {
		A[i] = rand();
	}
	
	struct atom p;
	p.l = 0;
	p.r = n;
    long start_timer = get_current_time();
#ifdef THREAD	
	pthread_t tid;
    pthread_create(&tid, NULL, my_merge_sort, (void*)&p);
	pthread_join(tid, NULL);
#endif

#ifdef NO_THREAD
	my_merge_sort((void *)&p);
#endif
    long end_timer = get_current_time();
	/*
	for(int i = 0; i < size; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
	*/
	printf("return %s\n", check(A, n) ? "true" : "false");
    printf("time %ldms\n", end_timer - start_timer);
	pthread_exit(NULL);
}

int main() {
	test(A, 10000000);
	return 0;
}

