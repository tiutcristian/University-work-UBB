#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int a2b, b2a;
	a2b = open("a2b", O_WRONLY);
        b2a = open("b2a", O_RDONLY);

	int a, b, s, p; 
	while(1) {
		printf("a = "); scanf("%d", &a);
		printf("b = "); scanf("%d", &b);

		write(a2b, &a, sizeof(int));
		write(a2b, &b, sizeof(int));
		if (read(b2a, &s, sizeof(int)) <= 0) {
                        close(a2b);
                        close(b2a);
                        break;
                }
                if (read(b2a, &p, sizeof(int)) <= 0) {
                        close(a2b);
                        close(b2a);
                        break;
                }

		printf("s = %d\n", s);
		printf("p = %d\n", p);

		if (s == p) {
                        printf("Exiting...\n");
                        break;
                }
	}

	close(a2b); close(b2a);
}
