#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int checkPrime(int n) {
	if(n<2)
		return 0;
	if(n==2)
		return 1;
	if(n%2==0)
		return 0;
	for(int i = 3; i*i <= n; i++)
		if(n%i==0)
			return 0;
	return 1;
}

int main() {
	int n;
	printf("n = ");
	scanf("%d", &n);
	for(int i = 2; i <= n; i++) {
		if(fork()==0)
			exit(checkPrime(i));
		int st;
		wait(&st);
		if(WEXITSTATUS(st)) {
			printf("%d ",i);
			fflush(stdout);
		}
	}
	printf("\n");
	return 0;
}
