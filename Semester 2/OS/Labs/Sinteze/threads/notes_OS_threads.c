#include <pthread.h>

#define CONDITION 0

int main()
{

//*	Mutex:
//	================================================================
	pthread_mutex_t mutex; // global variable
	
	pthread_mutex_init(&mutex, NULL);
	
	pthread_mutex_lock(&mutex);
	//! critical section
	pthread_mutex_unlock(&mutex);
	
	pthread_mutex_destroy(&mutex);
//	================================================================
	
	
//*	Conditional variables:
//	================================================================
	pthread_cond_t cond; // global variable
	
	pthread_cond_init(&cond, NULL);
	
	pthread_mutex_lock(&mutex);
	while (CONDITION == 0)
		pthread_cond_wait(&cond, &mutex);
	//! do what you have to do when CONDITION is true
	pthread_mutex_unlock(&mutex);
	
	pthread_mutex_lock(&mutex);
	//! critical section (that may modify CONDITION)
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	
	pthread_cond_destroy(&cond);
//	================================================================


//* Barriers
//	================================================================

	pthread_barrier_t barrier; // global variable
	
	pthread_barrier_init(&barrier, NULL, 3);
	
	// thread 1
	//!  do something you need all threads to wait for
	pthread_barrier_wait(&barrier);

	// thread 2
	//!  do something you need all threads to wait for
	pthread_barrier_wait(&barrier);
	
	// thread 3 - wait here for all threads to reach this point
	pthread_barrier_wait(&barrier);
	
	pthread_barrier_destroy(&barrier);
//	================================================================

//* Read-Write Locks
//	================================================================
	pthread_rwlock_t rwlock; // global variable
	
	pthread_rwlock_init(&rwlock, NULL);
	
	pthread_rwlock_rdlock(&rwlock);
	//! read something
	pthread_rwlock_unlock(&rwlock);
	
	pthread_rwlock_wrlock(&rwlock);
	//! write something
	pthread_rwlock_unlock(&rwlock);
	
	pthread_rwlock_destroy(&rwlock);

}