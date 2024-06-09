#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int* a;
int crt_len, n;
int control;

void print() {
    for(int i = 0; i < crt_len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void* f1(void* arg) { // adding even numbers
    while (1) {
        pthread_mutex_lock(&lock);
        while(control != 1) {
            pthread_cond_wait(&cond, &lock);
        }
        if (crt_len >= n) {
            control = 2;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }
        a[crt_len] = (rand() % 100) * 2;
        crt_len++;
        print();
        control = 2;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* f2(void* arg) { // adding odd numbers
    while(1) {
        pthread_mutex_lock(&lock);
        while(control != 2) {
            pthread_cond_wait(&cond, &lock);
        }
        if (crt_len >= n) {
            control = 1;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }
        a[crt_len] = (rand() % 100) * 2 + 1;
        crt_len++;
        print();
        control = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main (int argc, char *argv[]) {
    srand(time(NULL));
    crt_len = argc-1;
    printf("crt_len = %d\n", crt_len);
    printf("n = ");
    scanf("%d", &n);
    a = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < argc-1; i++) {
        a[i] = atoi(argv[i+1]);
    }
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    control = 1;
    print();
    pthread_create(&t1, NULL, f1, NULL);
    pthread_create(&t2, NULL, f2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);
    free(a);
    return 0;
}
