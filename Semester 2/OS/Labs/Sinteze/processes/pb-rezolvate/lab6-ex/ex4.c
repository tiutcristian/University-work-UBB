// Scrieți un program care fork()-uie procese copil recursiv c�tă vreme PID-ul fiecărui copil e par.

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void f() {
	int pid = fork();
	printf("[Entered] - pid=%d\n", pid);
	if (pid && pid%2 == 0)
		f();
}

int main() {
	f();
	return 0;
}
