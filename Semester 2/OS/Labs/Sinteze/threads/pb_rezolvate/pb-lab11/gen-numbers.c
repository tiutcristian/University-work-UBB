#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int cnt = atoi(argv[1]);
    FILE* f = fopen("numbers.txt", "w");
    fprintf(f, "%d\n", cnt);
    for (int i = 0; i < cnt; i++) {
        fprintf(f, "%d ", rand() % 1000);
    }
    return 0;
}