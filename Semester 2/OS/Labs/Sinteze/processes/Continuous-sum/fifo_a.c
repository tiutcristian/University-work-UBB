#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int a, b, s, p, a2b, b2a;
	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	while(1) {
		printf("a = "); scanf("%d", &a);

		printf("b = "); scanf("%d", &b);
		
		write(a2b, &a, sizeof(int));
		write(a2b, &b, sizeof(int));
		
		if(read(b2a, &s, sizeof(int)) <= 0) {
			printf("Couldn't read sum from b2a\n");
			break;
		}
		if(read(b2a, &p, sizeof(int)) <= 0) {
			printf("Couldn't read product from b2a\n");
			break;
		}
		
		printf("s = %d\n", s);
		printf("p = %d\n", p);
		
		if(s == p) {
			printf("Sum equal to product.\nExiting...\n");
			break;
		}
	}

	close(a2b); close(b2a);
}
