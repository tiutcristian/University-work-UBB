// Implement a program that continuously reads two integers from the console, 
// sends them to another process, gets back from that process their sum and product, 
// and display them to the console. 
// The program stops when the sum and the product are equal.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int p2c[2], c2p[2];
	pipe(p2c); pipe(c2p);
	if (fork()==0) {
		close(p2c[1]); close(c2p[0]);
		while(1) {
			int a, b, s, p;
			read(p2c[0],&a,sizeof(int));
                	read(p2c[0],&b,sizeof(int));
			s = a+b;
			p = a*b;
                	write(c2p[1],&s,sizeof(int));
                	write(c2p[1],&p,sizeof(int));
			if (s == p)
				break;
		}
		exit(0);
	}
	close(p2c[0]); close(c2p[1]);
	while(1) {
		int a, b, s, p;
		printf("a = ");
		scanf("%d", &a);
		printf("b = ");
                scanf("%d", &b);
		write(p2c[1],&a,sizeof(int));
		write(p2c[1],&b,sizeof(int));
		read(c2p[0],&s,sizeof(int));
		read(c2p[0],&p,sizeof(int));
		printf("s = %d\n", s);
		printf("p = %d\n", p);
		if (s == p)
			break;
	}
	wait(0);
	return 0;
}
