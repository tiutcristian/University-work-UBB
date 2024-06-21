#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	FILE* desc = fopen("fisier_mare.txt", "w");
	for(int i = 0; i < 5*1024*1024; i++) {
		fprintf(desc, ".");
	}
	fclose(desc);
}
