#include <signal.h>
#include <stdio.h>
#include <time.h>

void handler(int sig) {
	time_t tm = time(NULL);
        char* tmstr = ctime(&tm);
        printf("%s", tmstr);
}

int main() {
	signal(SIGHUP, handler);
	while(1);
}
