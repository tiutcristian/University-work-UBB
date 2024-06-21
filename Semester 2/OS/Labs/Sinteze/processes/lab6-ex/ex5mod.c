// ex5.c chnaged to work how it is expected

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int sum;

int main() {
        int* v;
        int n, p[2];
        printf("n = ");
        scanf("%d", &n);
        v=malloc(n*sizeof(int));
        for(int i = 0; i < n; i++)
                v[i] = i+1;
	pipe(p);
        if(fork()==0) {
		close(p[0]);
                for(int i = 0; i < n; i+=2)
                        sum += v[i];
		write(p[1],&sum,sizeof(int));
		close(p[1]);
                free(v);
                exit(0);
        }
	close(p[1]);
        for(int i = 1; i < n; i+=2)
                sum += v[i];
        free(v);
        wait(0);
	int auxsum;
	read(p[0],&auxsum,sizeof(int));
	close(p[0]);
	sum+=auxsum;
        printf("sum = %d\n",sum);
}
