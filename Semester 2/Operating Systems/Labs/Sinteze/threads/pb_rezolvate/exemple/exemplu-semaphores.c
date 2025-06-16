#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/shm.h>

//POSIX Semaphore test example using shared memory
# define SEGMENTSIZE sizeof(sem_t) // sem_t means semaphore type
# define SEGMENTPERM 0666
int main (int argc ,char ** argv )
{
	sem_t *sp;
	int retval, id, err ;
	if ( argc <= 1) {
		printf("Need shmem id. \n");
		exit (1) ;
	}
	sscanf( argv [1], "%d", &id); // Get id from command line
	printf(" Allocated %d\n", id);
	sp = (sem_t *) shmat (id ,( void *) 0, 0); // Attach the segment 
	if (( int ) sp == -1) {
		perror (" Attachment .");
		exit (2) ;
	}
	retval = sem_init (sp ,1 ,1) ; // Initialize the semaphore 
	if ( retval != 0) {
		perror(" Couldn’t initialize .");
		exit (3) ;
	}
	retval = sem_trywait (sp);
	printf("Did trywait . Returned %d >\n", retval ); getchar ();
	retval = sem_trywait (sp);
	printf("Did trywait . Returned %d >\n", retval ); getchar ();
	retval = sem_trywait (sp);
	printf("Did trywait . Returned %d >\n", retval ); getchar ();
	err = shmdt (( void *) sp); // Remove segment
	if (err == -1)
		perror (" Detachment .");
	return 0;
}

