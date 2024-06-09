#include <stdio.h>

int main() {
	FILE* f1 = fopen("fisier_mare.txt", "r");
	FILE* f2 = fopen("fisier_mare.txt.crypt.crypt", "r");

	char c1 = getc(f1); 
	char c2 = getc(f2); 

	int i = 0, j = 0;

	while(!feof(f1) && !feof(f2)) {
		j++;
		if (c1 != c2) {
			printf("%c - %c\n", c1, c2);
			i++;
		}
		c1 = getc(f1);
		c2 = getc(f2);
	}

	//printf("%d diferite\n", i);
	//printf("%d in total", j);
	printf("\n");

	fclose(f1);
	fclose(f2);
	return 0;
}
