#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N_THREADS 4
#define DIM_MATRIX 9

int m1[DIM_MATRIX][DIM_MATRIX];
int m2[DIM_MATRIX][DIM_MATRIX];
int res[DIM_MATRIX][DIM_MATRIX];

void generate_matrix(int m[DIM_MATRIX][DIM_MATRIX]) {
	for(int i = 0; i < DIM_MATRIX; i++) {
		for (int j = 0; j < DIM_MATRIX; j++) {
			m[i][j] = rand() % 90 + 10;
		}
	}
}

void print_matrix(int m[DIM_MATRIX][DIM_MATRIX]) {
	for (int i = 0; i < DIM_MATRIX; i++) {
		printf("| ");
		for(int j = 0; j < DIM_MATRIX; j++) {
			printf("%d ", m[i][j]);
		}
		printf("|\n");
	}
	printf("\n\n");
}

void* f(void* param) {
	int index = *(int*) param;
	int l = 0, c = index;
	while(l < DIM_MATRIX) {
		for(int i = 0; i < DIM_MATRIX; i++) {
			res[l][c] += m1[l][i] * m2[i][c];
		}
		l += (c+N_THREADS) / DIM_MATRIX;
		c = (c+N_THREADS) % DIM_MATRIX;
	}
	return NULL;
}

int main(int argc, char** argv) {
	srand(time(NULL));
	generate_matrix(m1);
	print_matrix(m1);
	generate_matrix(m2);
	print_matrix(m2);
	
	pthread_t t[N_THREADS];
	int index[N_THREADS];

	for(int i = 0; i < N_THREADS; i++) {
		index[i] = i;
		pthread_create(&t[i], NULL, f, (void*)&index[i]);
	}

	for(int i = 0; i < N_THREADS; i++) {
		pthread_join(t[i], NULL);
	}

	print_matrix(res);

	return 0;
}
