#include <signal.h>

int main() {
	signal(SIGTERM, SIG_IGN);
	while(1);
}
