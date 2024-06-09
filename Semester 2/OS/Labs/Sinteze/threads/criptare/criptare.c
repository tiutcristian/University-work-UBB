#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct{
	char filename[100];
	char key;
} param;

void* f(void* parametru) {
	param* p = (param*) parametru;

	FILE* readfile = fopen(p->filename, "r");
	char* writefilename = (char*)malloc(106);
        strcpy(writefilename, p->filename);
        strcat(writefilename, ".crypt");
        FILE* writefile = fopen(writefilename, "w");

        char c = fgetc(readfile);
        while (!feof(readfile)) {
		c = c ^ p->key;
                fputc(c, writefile);
                c = fgetc(readfile);
        }
        fclose(readfile);
        fclose(writefile);

	return writefilename;
}

int main()
{
	char filename[100];
	char key[2];
	printf("Introduceti nume fisier:\n");
	fgets(filename, 100, stdin);
	filename[strlen(filename)-1] = '\0';
	printf("Introduceti cheie criptare:\n");
	read(0, key, 2);

	pthread_t t;
	param* p = (param*)malloc(sizeof(param));
	strcpy(p->filename, filename);
	p->key = key[0];
	pthread_create(&t, NULL, &f, (void*)p);
	char* writefilename;
	pthread_join(t, (void**)&writefilename);

	printf("Content: ==========================\n");
	FILE* writefile = fopen(writefilename, "r");
	char c = fgetc(writefile);
        while (!feof(writefile)) {
		putchar(c);
		//printf("[%d]", (int)c);
                c = fgetc(writefile);
        }
	fclose(writefile);
	printf("\n===================================\n");

	free(writefilename);
	free(p);
	return 0;
}
