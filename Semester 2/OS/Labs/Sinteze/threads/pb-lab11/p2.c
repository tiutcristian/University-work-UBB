#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_AVIOANE 100

typedef struct {
    int id;
    int combustibil;
    int ora_decolare;
    int permisiune_aterizare;
    int permisiune_decolare;
} Avion;

Avion* aterizare[MAX_AVIOANE];
Avion* decolare[MAX_AVIOANE];
int count_aterizare = 0;
int count_decolare = 0;

pthread_mutex_t lock;
pthread_cond_t cond_d;
pthread_cond_t cond_a;
pthread_cond_t cond_gol;

void push_aterizare(Avion* a) {
	int pos = count_aterizare-1;
	count_aterizare++;
	while (pos >= 0 && aterizare[pos]->combustibil < a->combustibil) {
		aterizare[pos+1] = aterizare[pos];
		pos--;
	}
	aterizare[pos+1] = a;
	pthread_cond_signal(&cond_gol); // signal(cond)
}

void push_decolare(Avion* a) {
	int pos = count_decolare-1;
        count_decolare++;
        while (pos >= 0 && decolare[pos]->ora_decolare < a->ora_decolare) {
                decolare[pos+1] = decolare[pos];
                pos--;
        }
        decolare[pos+1] = a;
	pthread_cond_signal(&cond_gol); // signal(cond)
}

Avion* pop_aterizare() {
	Avion* a = aterizare[count_aterizare-1];
	count_aterizare--;
	return a;
}

Avion* pop_decolare() {
	Avion* a = decolare[count_decolare-1];
        count_decolare--;
	return a;
}

void* thread_avion(void* param) {
	Avion* a = (Avion*)param;
	push_aterizare(a); // adaugat in coada aterizare
	while(a->permisiune_aterizare == 0)// while nu are permisiune de aterizare
		pthread_cond_wait(&cond_a, &lock); //wait(cond)
	// (cand primeste permisiune de aterizare)
	printf("Avionul %d aterizeaza\n", a->id); // [aterizare]
	sleep(1); // (sleep 1)
	
	while(a->permisiune_decolare == 0)// while nu are permisiune de decolare
		pthread_cond_wait(&cond_d, &lock); //wait(cond)
	// (cand primeste permisiune de decolare)
	printf("Avionul %d decoleaza\n", a->id); // [decolare]
	sleep(1); // (sleep 1)
	return NULL;
}

void handle_aterizare() {
	Avion* a = pop_aterizare(); // avion = pop din aterizare
	a->permisiune_aterizare = 1; // dat la avion permisiune de aterizare
 	push_decolare(a); // push avion in decolare	
	pthread_cond_signal(&cond_a); // signal(cond)
}

void handle_decolare() {
	Avion* a = pop_decolare(); // avion = pop din decolare
	a->permisiune_decolare = 1; // dat la avion permisiune de decolare
	pthread_cond_signal(&cond_d); // signal(cond)
}

int comp_comb_dec() {
	Avion* a = aterizare[count_aterizare-1];
	Avion* b = decolare[count_decolare-1];
	return a->combustibil < b->ora_decolare;
}

void* thread_daemon(void* param) {
	while(1) {
		pthread_mutex_lock(&lock);// lock(mutex)
		while(count_aterizare == 0 && count_decolare == 0)
			pthread_cond_wait(&cond_gol, &lock); // signal(cond)
		// (cand unul din ele devine >0)
		if (count_aterizare > 0) {
			if (count_decolare > 0) {	
				if (comp_comb_dec()) { // comparare combustibil ramas 
						       // si ora de decolare
				// daca alegem avionul din coada de aterizare
				 	handle_aterizare();
				} else {
				 	handle_decolare();
				}
			} else {
				handle_aterizare();
			}
		} else {
			handle_decolare();
		}

		pthread_mutex_unlock(&lock);// unlock(mutex)
	}
	return NULL;	
}

void creare_avion(Avion* a) {
	a = (Avion*)malloc(sizeof(Avion));
	a->combustibil = rand() % 100 + 1;
	a->ora_decolare = rand() % 24;
	a->permisiune_aterizare = 0;
	a->permisiune_decolare = 0;
}

int main() {
	printf("ok");	
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond_d, NULL);
	pthread_cond_init(&cond_a, NULL);
	pthread_cond_init(&cond_gol, NULL);



	srand(time(NULL));
	pthread_t daemon_tid;
	pthread_t avioane_tid[MAX_AVIOANE];
	Avion* avioane[MAX_AVIOANE];

	pthread_create(&daemon_tid, NULL, thread_daemon, NULL);

	for (int i = 0; i < MAX_AVIOANE; i++) {
		creare_avion(avioane[i]);
		avioane[i]->id = i;
		pthread_create(&avioane_tid[i], NULL, thread_avion, (void*)avioane[i]);
		sleep(rand() % 3);
	}

	for (int i = 0; i < MAX_AVIOANE; i++) {
		pthread_join(avioane_tid[i], NULL);
	}

	for (int i = 0; i < MAX_AVIOANE; i++) {
		free(avioane[i]);
	}

	pthread_cancel(daemon_tid);
	pthread_join(daemon_tid, NULL);
	pthread_cond_destroy(&cond_d);
	pthread_cond_destroy(&cond_a);
	pthread_cond_destroy(&cond_gol);
	pthread_mutex_destroy(&lock);
	
	return 0;
}
