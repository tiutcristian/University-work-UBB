/*
 *
 * Write a program that creates 5 threads, giving each thread a string as parameter. 
 * Each thread will count and add to the global variables v and n as follows: 
 * 	the number of vowels contained by the string added to v
 * 	the number of digits contained in the string added to n.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THR_COUNT 5

int global_v = 0;
int gloabl_n = 0;
int next_string = 0;

void* compute_sums(void* param)
{
	// ...
}

int main()
{
	int no_of_strings;
	char** strings_array;

	scanf("%d", &no_of_strings);
	printf("nr=%d", no_of_strings);
	return 0;
}

/*
while (true) {
	if (gloabala < nr)
		unlock_mutex()
}
*/

/*
while(next_string < nr) {
	// do stuff ...
}
*/
