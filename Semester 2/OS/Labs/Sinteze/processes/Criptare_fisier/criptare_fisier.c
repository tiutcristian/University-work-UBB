#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
	char key, filename[100];
	
	printf("Enter name of file: \n");
	int cnt=read(0,filename,99);
	filename[cnt-1]='\0';

	printf("Enter key: \n");
       	scanf("%c",&key);

	if (fork() == 0)
	{
		FILE* readFileDesc = fopen(filename, "r");
		char writefilename[106];
		strcpy(writefilename, filename);
		strcat(writefilename, ".crypt");
		FILE* writeFileDesc = fopen(writefilename, "w");
		char crtChar;
		while(fread(&crtChar, 1, 1, readFileDesc)) {
			crtChar=crtChar^key;
			fwrite(&crtChar, 1, 1, writeFileDesc);
		}
		fclose(readFileDesc);
		fclose(writeFileDesc);
		exit(0);
	}
	wait(0);


	return 0;

}
