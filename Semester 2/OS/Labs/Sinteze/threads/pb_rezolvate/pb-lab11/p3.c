#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int len;
int* sir;

void sortare(int begin, int end) {
	int i, j, aux;
	for(i = begin; i < end; i++) {
		for(j = i+1; j <= end; j++) {
			if(sir[i] > sir[j]) {
				aux = sir[i];
				sir[i] = sir[j];
				sir[j] = aux;
			}
		}
	}
}

void* t2(void* param) {
	sortare(0, len/2-1);
	return NULL;
}

void* t3(void* param) {
	sortare(len/2, len-1);
	return NULL;
}

void* t1(void* param) {
	pthread_t thr2, thr3;
	pthread_create(&thr2, NULL, t2, NULL);
	pthread_create(&thr3, NULL, t3, NULL);
	pthread_join(thr2, NULL);
	pthread_join(thr3, NULL);
	int* sirnou = (int*)malloc(len*sizeof(int));
	int lennou = 0;
	int i = 0, j = len/2;
	while(i < len/2 && j < len) {
		if(sir[i] < sir[j]) {
			sirnou[lennou] = sir[i];
			i++;
		} else {
			sirnou[lennou] = sir[j];
                        j++;
		}
		lennou++;
	}
	while(i < len/2) {
		sirnou[lennou] = sir[i];
		i++;
		lennou++;
	}
	while(j < len) {
		sirnou[lennou] = sir[j];
		j++;
		lennou++;
	}
	free(sir);
	sir = sirnou;
	return NULL;
}

int main() {

//	printf("Enter length: ");
	scanf("%d", &len);
	sir = (int*)malloc(len * sizeof(int));
//	printf("Enter elems: ");
	for(int i = 0; i < len; i++) {
		scanf("%d", &sir[i]);
	}

	pthread_t t;

	time_t start = time(NULL);
	pthread_create(&t, NULL, t1, NULL);
	pthread_join(t, NULL);
	time_t end = time(NULL);	

	double x = difftime(end, start);
	printf("Execution time: %.0f\n", x);
//	printf("Sorted array: ");
//	for(int i = 0; i < len; i++) {
//		printf("%d ", sir[i]);
//	}
//	printf("\n");

	free(sir);
	return 0;
}
