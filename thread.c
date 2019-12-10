#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 5

int sum = 0;
pthread_mutex_t lock;

void *run (void * args){
    pthread_mutex_lock(&lock);

    for(int i = 0; i < 10000000; i++) sum += 1;

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main (){
    pthread_t thread_id[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) pthread_create(&thread_id[i], NULL, run, NULL);

    for(int i = 0; i < NUM_THREADS; i++) pthread_join(thread_id[i], NULL);

    printf("Sum %d\n", sum);
    printf("End of the Program\n");
    pthread_mutex_destroy(&lock);

    return 0;
}