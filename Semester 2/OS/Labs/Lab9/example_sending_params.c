#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>





// define a constant for the number of threads

#define THR_COUNT 4



// This function will be executed by each thread

void* thread_function(void *param)

{

    int nr = *(int*)param;

    printf("I am thread %lu and I received the value %d\n", (ulong)pthread_self(), nr);

    

    return 0;

}



int main()

{

    int i = 0;

    pthread_t thr[THR_COUNT];



    int thr_param[THR_COUNT];



    for (i = 0; i < THR_COUNT; i++)

    {

        // prepare the parameters

        // thr_param[i] = i;



        // create the threads

        pthread_create(&thr[i], NULL, thread_function, (void*)&i);

    }



   // wait for the threads to terminate

    for (i = 0; i < THR_COUNT; i++)

    {

        pthread_join(thr[i], NULL);

    }



    return 0;

}
