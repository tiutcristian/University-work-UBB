#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>



// define a constant for the size of the array

#define ARR_SIZE 10000



// define a constant for the number of threads

#define THR_COUNT 4



// define a structure used to send parameters to the threads

typedef struct _THR_PARAM

{ 

    int *array;     // the array to process

    int idx_start;  // the start index in the array

    int idx_end;    // the end index in the array

}THR_PARAM;



// global variable - the sum of the elements in the array

int global_sum = 0;



// thread function - computes the sum of the elements of an array within a certain range

void* array_sum(void *param)

{

    THR_PARAM thr_param;

    int i;

    

    // we will use a local variable to compute the sum

    int local_sum = 0;  



    thr_param = *(THR_PARAM*)param;

    

    // iterate the elements of the array 

    for (i = thr_param.idx_start; i < thr_param.idx_end; i++)

    {

        local_sum = local_sum + thr_param.array[i];

    }



    // add the sum computed by the thread to the global sum 

    global_sum = global_sum + local_sum;

  

    return 0;

}



int main()

{

    int i;

    int array[ARR_SIZE];

    pthread_t thr[THR_COUNT];

    THR_PARAM thr_param[THR_COUNT];



    // fill the array with 1s - easier to compute

    for (i = 0; i < ARR_SIZE; i++)

    {

        array[i] = 1;

    }



    // prepare the params for each thread and create it 

    for (i = 0; i < THR_COUNT; i++)

    {

        // prepare the params for the thread: the array, the start index, the end index 

        thr_param[i].array = array;

        thr_param[i].idx_start = (ARR_SIZE / THR_COUNT) * i;

        thr_param[i].idx_end = (ARR_SIZE / THR_COUNT) * (i + 1);



        // create the thread

        pthread_create(&thr[i], NULL, array_sum, (void*)&thr_param[i]);

    }



    // wait for the threads to complete

    for (i = 0; i < THR_COUNT; i++)

    {

        pthread_join(thr[i], NULL);

    }



    // display the sum

    printf("Sum = %d\n", global_sum);



    return 0;

}
