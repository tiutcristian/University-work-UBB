// Citiți o comandă de la tastatură și rulați-o cu fork + exec
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

	char command[50];
	printf("Enter command: ");
	scanf("%s",command);
	fflush(stdin);

	printf("[COMMAND ENTERED]\n");
	if (fork()==0) {
		printf("[ENTERED IN CHILD]\n");
		execlp(command, command, NULL);
		printf("[THIS SHOULD NOT BE DISPLAYED]\n");
		exit(0);
	}
	wait(0);
	printf("[RETURNED IN PARENT]\n");

	return 0;
}
