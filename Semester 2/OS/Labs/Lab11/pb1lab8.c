// Write a program that creates 5 threads, giving each thread a string as parameter. 
// Each thread will count and add to the global variables v and n as follows: 
// the number of vowels contained by the string added to v, 
// and the number of digits contained in the string added to n.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

int n, v;
pthread_mutex_t lock;

void* f(void* param) {
	char str[100];
	int n_loc = 0, v_loc = 0;
	strcpy(str, (char*)param);
	for(int i = 0; i < strlen(str); i++) {
		if(isdigit(str[i]))
			n_loc++;
		else if(strchr("aeiouAEIOU", str[i]))
			v_loc++;
	}
	pthread_mutex_lock(&lock);
	n += n_loc;
	v += v_loc;
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main() {
	pthread_t t[5];
	pthread_mutex_init(&lock, NULL);

	char strings[5][100];
	strcpy(strings[0], "aeiou");
	strcpy(strings[1], "12345");
	strcpy(strings[2], "crlftpd");
	strcpy(strings[3], "ana are 4 mere");
	strcpy(strings[4], "99 bottles of beer");
	for (int i = 0; i < 5; i++) {
		pthread_create(&t[i], NULL, f, (void*)&strings[i]);
	}

	for (int i = 0; i < 5; i++) {
		pthread_join(t[i], NULL);
	}

	pthread_mutex_destroy(&lock);

	printf("No. of digits: %d\n", n);
	printf("No. of vowels: %d\n", v);

}
