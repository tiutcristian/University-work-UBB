#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid, state;
    printf(" The parent: before the fork()\n");
    if ((pid = fork()) != 0)
    {
        wait(&state);
    }
    else
    {
        int pid;
        printf("The child: begins the execution \n");
        pid=getpid();
        printf("The son: %d terminates\n", pid);
        exit(10);
    }
 
    printf("The parent: after fork()\n");
    int stateClean = WEXITSTATUS(state);
    printf("PID child=%d; terminated with the code %d=%x\nand clean state is %d=%x\n", pid, state, state, stateClean, stateClean);
}
