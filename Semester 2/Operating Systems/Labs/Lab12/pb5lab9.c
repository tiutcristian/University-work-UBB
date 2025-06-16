#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>

static const int NO_OF_THREADS = 8;
//const int NO_OF_THREADS = 8;
static const int N = 20000000;
//const int N = 20000;
static const int CAP = N/NO_OF_THREADS;
//const int CAP = N/NO_OF_THREADS;

int n;
pthread_mutex_t lock;

int check_prime(int nr) {
	if (nr < 2) return 0;
        if (nr == 2) return 1;
        if (nr%2 == 0) return 0;
        else for (int i = 3; i*i <= nr; i++) if (nr%i == 0) return 0;
	return 1;
}

void* process_prime(void* param) {
	int index = *(int*) param;
	int start = index*CAP;
	int end;
	if (index == NO_OF_THREADS-1)
		end = N;
	else
		end = (index+1)*CAP;
	printf("%d - %d\n", start, end);

	int local_cnt = 0;
	for(int nr = start; nr <= end; nr++)
		local_cnt += check_prime(nr);

	pthread_mutex_lock(&lock);
	n += local_cnt;
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(int argc, char** argv) {
        pthread_t t[NO_OF_THREADS];
        pthread_mutex_init(&lock, NULL);
	int indexes[NO_OF_THREADS];

	for (int i = 0; i < NO_OF_THREADS; i++)
		indexes[i] = i;

        for (int i = 0; i < NO_OF_THREADS; i++)
                pthread_create(&t[i], NULL, process_prime, (void*)&indexes[i]);

        for (int i = 0; i < NO_OF_THREADS; i++)
                pthread_join(t[i], NULL);

        pthread_mutex_destroy(&lock);

        printf("No. of numbers prime numbers between 1 and %d: %d\n", N, n);

}
