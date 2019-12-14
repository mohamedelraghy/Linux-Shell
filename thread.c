#include <stdio.h>
#include <string.h>
#include <pthread.h>
#define NUM_THREADS 5 // Num of threads 

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

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    int err;
    for(int i = 0; i < NUM_THREADS; i++){

        err = pthread_create(&thread_id[i], NULL, run, NULL);
        if (err != 0) printf("\nThread can't be created :[%s]",strerror(err));
    } 

    for(int i = 0; i < NUM_THREADS; i++) pthread_join(thread_id[i], NULL);

    printf("Sum = %d\n", sum);
    printf("End of the Program\n");
    pthread_mutex_destroy(&lock);
    

    return 0;
}
