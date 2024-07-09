// The program will not display the sum correctly because fork will make a copy of the memory
// for the child and it can not write to the global variable of its parent.
// For this we will need to use pipe communication (see ex5mod.c)

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int sum;

int main() {
	int* v;
	int n;
	printf("n = ");
	scanf("%d", &n);
	v=malloc(n*sizeof(int));
	for(int i = 0; i < n; i++)
		v[i] = i+1;
	if(fork()==0) {
		for(int i = 0; i < n; i+=2)
			sum += v[i];
		free(v);
		exit(0);
	}
	for(int i = 1; i < n; i+=2)
		sum += v[i];
	free(v);
	wait(0);
	printf("sum = %d\n",sum);
}
