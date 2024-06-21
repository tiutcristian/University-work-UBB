#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pid, state;
    char filename[100];
    char key[2];
    printf("Introduceti nume fisier:\n");
    read(0, filename, 100);
    printf("Introduceti cheie criptare:\n");
    read(0, key, 2);
    if ((pid = fork()) != 0)
    {
        wait(&state);
    }
    else
    {
	FILE* readfile = fopen(filename, "r");
	char writefilename[106];
	strcpy(writefilename, filename);
	strcat(writefilename, ".crypt");
	FILE* writefile = fopen(writefilename, "w");

	char c = fgetc(readfile);
   	while (!feof(readfile)) {
      	    fputc(c, writefile);
      	    c = getc(readfile);
   	}
	fclose(readfile);
	fclose(writefile);
        exit(0);
    }
}
