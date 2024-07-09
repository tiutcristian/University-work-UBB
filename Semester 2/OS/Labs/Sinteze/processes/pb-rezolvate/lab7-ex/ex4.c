#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int p2c1[2], p2c2[2];
	int pid1, pid2;

	if(pipe(p2c1) == -1) {
		perror("pipe1");
		exit(EXIT_FAILURE);
	}

	if(pipe(p2c2) == -1) {
		perror("pipe2");
		exit(EXIT_FAILURE);
	}

	if((pid1 = fork())==0) {
		// copil 1
		close(p2c1[1]); close(p2c2[0]); close(p2c2[1]);
		char ch;
		int total_length;
		while (1) {
            		if (read(p2c1[0], &ch, 1) <= 0) {
                		break;
            		}
                	total_length++;
        	}

	        printf("Total length of words containing 'oa': %d\n", total_length);

		close(p2c1[0]);

		exit(EXIT_SUCCESS);
	}
	else if (pid1 == -1) {
		perror("fork1");
		exit(EXIT_FAILURE);
	}

	if((pid2 = fork())==0) {
		// copil 2
		close(p2c2[1]); close(p2c1[0]); close(p2c1[1]);

		char ch;
                int total_length;
                while (1) {
                        if (read(p2c2[0], &ch, 1) <= 0) {
                                break;
                        }
                        total_length++;
                }

                printf("Total length of words not containing 'oa': %d\n", total_length);

                close(p2c2[0]);

		exit(EXIT_SUCCESS);
	}
	else if(pid2 == -1) {
		
		perror("fork2");
		exit(EXIT_FAILURE);
	}

	// parinte
	
	close(p2c1[0]); close(p2c2[0]);

	char buf[100];
	while(1) {
		printf("Enter word: ");
		if (fgets(buf, 100, stdin) == NULL || buf[0] == '\n') {
			close(p2c1[1]); close(p2c2[1]);
			wait(NULL); wait(NULL);
			exit(EXIT_SUCCESS);
		}
		int len = strlen(buf);
		if (buf[len-1] == '\n') {
			buf[len-1] = '\0';
			len--;
		}
		if (strstr(buf, "oa") != NULL) {
			write(p2c1[1],buf,len);
		} else {
			write(p2c2[1],buf,len);
		}
	}

	wait(0); wait(0);
}
