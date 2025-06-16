// A C program receives command line args numbers, and creates for each a thread that checks is the numbers are multiple of 2 or 5, incrementing a global variable. (use atoi)

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>

int n;
pthread_mutex_t lock;

void* f(void* param) {
	int nr = *(int*)param;
	if(nr%2 == 0 || nr%5 == 0) {
		pthread_mutex_lock(&lock);
		n++;	
        	pthread_mutex_unlock(&lock);
	}
        return NULL;
}

int main(int argc, char** argv) {
        pthread_t t[argc-1];
        pthread_mutex_init(&lock, NULL);
	int numbers[argc-1];

	for (int i = 0; i < argc-1; i++) {
		numbers[i] = atoi(argv[i+1]);
	}

	for (int i = 0; i < argc-1; i++) {
		pthread_create(&t[i], NULL, f, (void*)&numbers[i]);
	}

        for (int i = 0; i < argc-1; i++) {
                pthread_join(t[i], NULL);
        }

        pthread_mutex_destroy(&lock);

        printf("No. of numbers divisible with 2 or 5: %d\n", n);

}

