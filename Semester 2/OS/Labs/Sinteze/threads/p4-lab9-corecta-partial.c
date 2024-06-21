#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int cnt = 0;
int v[1005];
pthread_mutex_t lock;
pthread_cond_t cond;
pthread_barrier_t barrier;

void* f(void* param) {
	while(1) {
		int nr = rand() % 1000;
		pthread_mutex_lock(&lock);

		if (cnt >= 1000) {
			pthread_mutex_unlock(&lock);
			break;
		}

		int pos = cnt-1;
		while(v[pos] > nr && pos >= 0) {
			v[pos+1] = v[pos];
			pos--;
		}
		v[pos+1] = nr;
		cnt++;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
		pthread_barrier_wait(&barrier);
	}
	return NULL;
}

int main() {
	srand(time(0));
	pthread_t t[5];
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_barrier_init(&barrier, NULL, 6);

	for(int i = 0; i < 5; i++) {
		pthread_create(&t[i], NULL, f, NULL);	
	}

	while(cnt < 1000) {
		pthread_mutex_lock (&lock);
		while (cnt % 10) {
			pthread_cond_wait (&cond, &lock);
		}
//		for(int i = 0; i < cnt; i++) {
//			printf("%d ", v[i]);
//		}
		printf("%d ", cnt);
		pthread_barrier_wait(&barrier);
//		printf("\n");
		pthread_mutex_unlock (&lock);
	}

	for(int i = 0; i < 5; i++) {
		pthread_join(t[i], NULL);
	}

//	for(int i = 0; i < cnt; i++)
//		printf("%d\n", v[i]);
//	printf("\n");

	pthread_barrier_destroy(&barrier);
	pthread_cond_destroy(&cond);	
	pthread_mutex_destroy(&lock);
	return 0;
}
