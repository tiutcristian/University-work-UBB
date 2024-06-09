#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
	int a, b, s, p, a2b, b2a;
        a2b = open("a2b", O_RDONLY);
        b2a = open("b2a", O_WRONLY);
	
	while(1) {
		if(read(a2b, &a, sizeof(int)) <= 0) {
                        printf("Couldn't read a from a2b\n");
			break;
                }
                if(read(a2b, &b, sizeof(int)) <= 0) {
                        printf("Couldn't read b from a2b\n");
                        break;
                }
		s = a+b;
		p = a*b;
		write(b2a, &s, sizeof(int));
		write(b2a, &p, sizeof(int));
		if (s == p) {
			printf("Sum equal to product.\nExiting...\n");
			break;
		}
	}

	close(a2b); close(b2a);
}

