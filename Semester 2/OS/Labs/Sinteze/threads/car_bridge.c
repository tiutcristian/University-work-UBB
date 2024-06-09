/*
 * Car bridge under reparation. There is a bridge over a river, that is under reparation. 
 * Use locks and condition variables to synchronize, in a C program, the threads simulating cars, 
 * such that the following conditions hold simultaneously:

1. Cars can pass the bridge in only one direction at one moment. The crossing direction is changed periodically (for instance, 
every 5 seconds) by another thread traffic_controller.

2. The maximum number of cars on the bridge is limited to MAX.

3. When the crossing direction is changed, the cars that are just given the permission to enter the bridge must wait 
until all the cars from the opposite direction exit the bridge.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 5

pthread_mutex_t lock;
pthread_cond_t cond[2];

int current_direction = 0;
int cars_on_bridge = 0;
int waiting_cars[2] = {0, 0};

struct car_args {
    int car_id;
    int car_direction;
};

void enter_bridge(int car_id, int car_direction) {
    pthread_mutex_lock(&lock);

    waiting_cars[car_direction]++;
    while (car_direction != current_direction || cars_on_bridge >= MAX) {
        pthread_cond_wait(&cond[car_direction], &lock);
    }
    waiting_cars[car_direction]--;
    cars_on_bridge++;
    printf("Car %d entering the bridge in direction %d\n", car_id, car_direction);

    pthread_mutex_unlock(&lock);
}

void pass_bridge(int car_id, int car_direction) {
    printf("Car %d passing the bridge in direction %d\n", car_id, car_direction);
    sleep(1);  // Simulate time taken to pass the bridge
}

void exit_bridge(int car_id, int car_direction) {
    pthread_mutex_lock(&lock);

    cars_on_bridge--;
    printf("Car %d exiting the bridge in direction %d\n", car_id, car_direction);
    if (cars_on_bridge == 0 && waiting_cars[1 - car_direction] > 0) {
        pthread_cond_broadcast(&cond[1 - car_direction]);
    }

    pthread_mutex_unlock(&lock);
pthread_cond_broadcast}

void* car(void* arg) {
    struct car_args* car_arg = (struct car_args*) arg;
    enter_bridge(car_arg->car_id, car_arg->car_direction);
    pass_bridge(car_arg->car_id, car_arg->car_direction);
    exit_bridge(car_arg->car_id, car_arg->car_direction);

    return NULL;
}

void change_passing_direction() {
    pthread_mutex_lock(&lock);

    current_direction = 1 - current_direction;
    printf("Changing direction to %d\n", current_direction);
    if (waiting_cars[current_direction] > 0 && cars_on_bridge == 0) {
        pthread_cond_broadcast(&cond[current_direction]);
    }

    pthread_mutex_unlock(&lock);
}

void* traffic_controller(void* arg) {
    while (1) {
        sleep(5);
        change_passing_direction();
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond[0], NULL);
    pthread_cond_init(&cond[1], NULL);

    pthread_t car_threads[100];
    struct car_args car_args[100];
    pthread_t controller_thread;

    pthread_create(&controller_thread, NULL, traffic_controller, NULL);

    for (int i = 0; i < 100; i++) {
        car_args[i].car_id = i;
        car_args[i].car_direction = i % 2;
        pthread_create(&car_threads[i], NULL, car, &car_args[i]);
    }

    for (int i = 0; i < 100; i++) {
        pthread_join(car_threads[i], NULL);
    }

    pthread_join(controller_thread, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond[0]);
    pthread_cond_destroy(&cond[1]);

    return 0;
}

