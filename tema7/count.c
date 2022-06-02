#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_RESOURCES 8

void msleep(int millis) {
    struct timespec ts = {
        .tv_sec = 0,
        .tv_nsec = millis * 1000,
    };
    nanosleep(&ts, NULL);
}

int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
int decrease_count(int count) {
    pthread_mutex_lock(&mutex);
 
    if (available_resources < count) {
        pthread_mutex_unlock(&mutex);
        return -1;
    }
 
    available_resources -= count;
 
    pthread_mutex_unlock(&mutex);
 
    return 0;
}
 
int increase_count(int count) {
    pthread_mutex_lock(&mutex);
 
    available_resources += count;
 
    pthread_mutex_unlock(&mutex);
 
    return 0;
}
 
void* use_resources(void* input) {
    int amount = (rand() % (MAX_RESOURCES * 2 / 3)) + 1;
 
    if (decrease_count(amount) == 0) {
        printf("Got %d resources, remaining %d\n", amount, available_resources);
 
        msleep(100);
 
        increase_count(amount);
        printf("Released %d resources, remaining %d\n", amount, available_resources);
    } else {
        printf("Failed to acquire %d resources\n", amount);
    }
 
    return NULL;
}
 
int main() {
    int num_threads = 4;
 
    pthread_t* worker_ids = malloc(sizeof(pthread_t) * num_threads);
    for (int i = 0; i < num_threads; ++i) {
        pthread_create(&worker_ids[i], NULL, use_resources, NULL);
    }
 
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(worker_ids[i], NULL);
    }

    return 0;
}
