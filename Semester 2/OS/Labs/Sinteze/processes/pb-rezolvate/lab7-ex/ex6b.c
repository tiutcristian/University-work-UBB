#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int a2b, b2a;
	a2b = open("a2b", O_RDONLY);
	b2a = open("b2a", O_WRONLY);

	int a, b, s, p;
	while(1) {
		if (read(a2b, &a, sizeof(int)) <= 0) {
			close(a2b);
			close(b2a);
			break;
		}
		if (read(a2b, &b, sizeof(int)) <= 0) {
			close(a2b);
			close(b2a);
			break;
		}
		s = a+b;
		p = a*b;
		write(b2a, &s, sizeof(int));
		write(b2a, &p, sizeof(int));
		if (s == p) {
			printf("Exiting...\n");
			break;
		}
	}

	close(a2b); close(b2a);
}
