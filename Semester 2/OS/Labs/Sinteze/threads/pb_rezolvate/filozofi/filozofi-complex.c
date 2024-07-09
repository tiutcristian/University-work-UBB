//O soluție care să asigure un maximum de paralelism este ca fiecare filosof să aibă câte două threaduri, unul de mâncare şi unul de cugetare. Pentru a mânca, se asociază fiecărui filosof o variabilă condiţională ce îi dă dreptul să mănânce. Apare un mic inconvenient: este posibil să apară la acelaşi filosof două cugetări consecutive, sau două mâncări consecutive . . .

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define FILOSOFI 5
#define MANANCA 1
#define CUGETA 2
#define FLAMAND 3
#define TRUE 1
#define FALSE 0
 
int stare[FILOSOFI];
int nt[FILOSOFI];
pthread_t t[2*FILOSOFI];
pthread_cond_t cond[FILOSOFI];
pthread_mutex_t mutex[FILOSOFI];

int poateManca(int i) { 
    int stanga = (i - 1 + FILOSOFI) % FILOSOFI;
    int dreapta = (i + 1) % FILOSOFI;
    if(stare[i] == FLAMAND && stare[stanga] != MANANCA && stare[dreapta] != MANANCA) { 
        stare[i] = MANANCA; 
        pthread_cond_signal(&cond[i]); 
        return TRUE; 
    } else 
        return FALSE;
}

void* mananca(void *n) {
    int i = *((int*)n); 
    while (TRUE) {
        pthread_mutex_lock(&mutex[i]); 
        stare[i] = FLAMAND; 
        while (poateManca(i) == FALSE) 
            pthread_cond_wait(&cond[i], &mutex[i]); 
        printf("%d mananca\n", i);
        pthread_mutex_unlock(&mutex[i]); 
        sleep(abs(rand()%2)); 
    }
}

void* cugeta(void *n) {
    int i = *((int*)n); 
    while (TRUE) {
        pthread_mutex_lock(&mutex[i]); 
        stare[i] = CUGETA; 
        printf("%d cugeta\n", i);
        pthread_mutex_unlock(&mutex[i]);
        sleep(abs(rand()%5)); 
    }
}

int main() {
    int i;
    for (i = 0; i < FILOSOFI; i++) {
        nt[i] = i;
        stare[i] = CUGETA;
        pthread_cond_init(&cond[i], NULL);
        pthread_mutex_init(&mutex[i], NULL);
    }
    for (i = 0; i < FILOSOFI; i++) {
        pthread_create(&t[i], NULL, mananca, &nt[i]);
        pthread_create(&t[i+FILOSOFI], NULL, cugeta, &nt[i]);
    }
    for (i = 0; i < 2*FILOSOFI; i++)
        pthread_join(t[i], NULL);
}