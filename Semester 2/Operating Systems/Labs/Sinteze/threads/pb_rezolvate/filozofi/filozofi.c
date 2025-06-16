//O soluţie simplă, dar cu un paralelism nu prea mare, se obţine dacă se asociază fiecărei furculiţe câte un mutex şi câte un thread fiecărui filosof. Sursa este:

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define N 5
int nt[N];
pthread_t t[N];
pthread_mutex_t mutex[N];

void* filosof(void *n) {
    int i = *((int*)n); 
    while(1) {
        pthread_mutex_lock(&mutex[i]); 
        pthread_mutex_lock(&mutex[(i + 1) % N]); 
        printf("%d mananca\n", i);
        pthread_mutex_unlock(&mutex[(i + 1) % N]); 
        pthread_mutex_unlock(&mutex[i]); 
        sleep(rand()%2); // Cam atat dureaza mancatul
        printf("%d cugeta\n", i);
        sleep(rand()%3); // Cam atat dureaza cugetatul 
    }
}

int main() {
    int i;
    for (i = 0; i < N; i++) {
        nt[i] = i;
        pthread_mutex_init(&mutex[i], NULL);
    }
    for (i = 0; i < N; i++)
        pthread_create(&t[i], NULL, filosof, &nt[i]);
    for (i = 0; i < N; i++)
        pthread_join(t[i], NULL);
}
