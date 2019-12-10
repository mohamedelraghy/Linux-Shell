#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 5

int sum = 0;


void *run (void * args){
    for(int i = 0; i < 10000000; i++) sum += 1;
    return NULL;
}

int main (){
    pthread_t thread_id[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) pthread_create(&thread_id[i], NULL, run, NULL);

    void * thread_return[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) pthread_join(thread_id[i], &thread_return[i]);

    printf("Sum %d", sum);
    printf("End of the Program\n");

    return 0;
}