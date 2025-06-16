#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define M 13
#define SLEEP 4
pthread_mutex_t mutcond;
pthread_cond_t cond;
int linie[N], tren[M], inA[M + 1], dinB[M + 1], liniilibere;
pthread_t tid[M];
time_t start;
void t2s(int *t, int l, char *r)
{
	int i;
	char n[10];
	sprintf(r, "[");
	for (i = 0; i < l; i++)
	{
		sprintf(n, "%d, ", t[i]);
		strcat(r, n);
	}
	i = strlen(r) - 1;
	if (r[i] == ' ')
		r[i - 1] = 0;
	strcat(r, "]");
}
void prinT(char *s, int t)
{
	int i;
	char a[200], l[200], b[200];

	i = 0;
	while (inA[i] != -1)
		i++;
	t2s(inA, i, a);

	t2s(linie, N, l);

	i = 0;
	while (dinB[i] != -1)
		i++;
	t2s(dinB, i, b);

	printf("%s %d\tA:%s\tLines:%s\tB:%s\ttime: %ld\n", s, t, a, l, b, time(NULL) - start);
}
// rutina unui thread
void *trece(void *tren)
{
	int i, t, l;
	t = *(int *)tren;
	sleep(1 + rand() % SLEEP);

	// ==========================================
	pthread_mutex_lock(&mutcond);

	i = 0;
	while (inA[i] != -1)
		i++;
	inA[i] = t;
	prinT("EnterA", t);

	while (liniilibere == 0)
		pthread_cond_wait(&cond, &mutcond);

	l = 0;
	while (linie[l] != -1)
		l++;
	linie[l] = t;
	liniilibere--;

	i = 0;
	while (inA[i] != t)
		i++;
	while (i < M) {
		inA[i] = inA[i + 1];
		i++;
	}
		
	prinT(" A => B", t);
	pthread_mutex_unlock(&mutcond);
	// ==========================================

	sleep(1 + rand() % SLEEP);

	// ==========================================
	pthread_mutex_lock(&mutcond);
	linie[l] = -1;
	liniilibere++;

	i = 0;
	while(dinB[i] != -1)
		i++;
	dinB[i] = t;
	prinT(" OutB", t);
	
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutcond);
	// ==========================================
}

int main(int argc, char *argv[])
{
	// initializari
	int i;
	start = time(NULL);
	pthread_mutex_init(&mutcond, NULL);
	pthread_cond_init(&cond, NULL);
	liniilibere = N;
	for (i = 0; i < N; i++)
		linie[i] = -1;
	for (i = 0; i < M; i++)
		tren[i] = i;
	for (i = 0; i < M + 1; i++) {
		inA[i] = -1;
		dinB[i] = -1;
	}

	// creare threaduri
	for (i = 0; i < M; i++)
		pthread_create(&tid[i], NULL, trece, &tren[i]);
	for (i = 0; i < M; i++)
		pthread_join(tid[i], NULL);

	// finalizari
	pthread_mutex_destroy(&mutcond);
	pthread_cond_destroy(&cond);
	return 0;
}
