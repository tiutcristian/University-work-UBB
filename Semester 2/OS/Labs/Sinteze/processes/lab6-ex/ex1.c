int i, j, k;

i = fork();

if ((j = fork())) {

    k = fork();

}

printf("%d %d %d %d %d", i, j, k, getpid(), getppid());
