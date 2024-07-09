#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t t1, t2;
pthread_barrier_t barrier;
void * thread1 (void *not_used){
	time_t now;
	char buf [27];
	time (&now);
	printf ("thread1 starting at %s", ctime_r (&now, buf));
	
	sleep (2);
	pthread_barrier_wait (&barrier);
	
	time (&now);
	printf ("barrier in thread1() done at %s", ctime_r (&now, buf));
	return NULL;
}

void * thread2 (void *not_used){
	time_t now;
	char buf [27];
	time (&now);
	printf ("thread2 starting at %s", ctime_r (&now, buf));
	
	sleep (4);
	pthread_barrier_wait (&barrier);
	
	time (&now);
	printf ("barrier in thread2() done at %s", ctime_r (&now, buf));
	return NULL;
}

int main (){
	time_t now;
	char buf [27];
	
	pthread_barrier_init (&barrier, NULL, 3);
	
	pthread_create(&t1, NULL, thread1, NULL);
	pthread_create(&t2, NULL, thread2, NULL);
	
	time(&now);
	printf("main waiting for barrier at %s", ctime_r (&now, buf));
	pthread_barrier_wait(&barrier);
	
	time(&now);
	printf("barrier in main () done at %s", ctime_r (&now, buf));
}

