#include <stdio.h> //remove if not using.
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include "util.h"//implementing
typedef struct 
{
    int count;
    pthread_mutex_t *pmtx;
    int max;
    int verbose; 
}ThreadData;
static int isPrime(int n)
{
    if(n == 1)
    {
        return 0;
    }
    else if(n == 2 || n == 3)
    {
        return 1;
    }

    int limit = sqrt((double) n);
    //printf("n = %d, limit = %d\n", n, limit);
    for(int i = 2; i <= limit; i++)
    {
        //printf("%d %% %d = %d\n", n, i, n % i);
        if(n % i == 0)
        {
          return 0;
        }
    }
    return 1;
}
static void* pickNext(void* arg){
    ThreadData* t = (ThreadData*) arg;
    int testVal = -1;
    while(t->count < t->max){
        pthread_mutex_lock(t->pmtx);
        testVal = t->count++;
        pthread_mutex_unlock(t->pmtx);
        if(t->verbose && isPrime(testVal)){
            printf("%d\n",testVal);
        }
    }
    
    pthread_exit(NULL);
}
void primes_st(unsigned int max, unsigned int verb){
    int i = 1;
    int limit = max;
    while(i <= limit)
    {
        if(isPrime(i) && verb)
        {
            printf("%d\n", i);
        }
        i++;
    }
    return;
}

void primes_mt(unsigned int max, unsigned int threads,	\
	       unsigned int verb){
    //Put your code here.
    //Remember to swap m and n in the data structure 
    //after performing the transposition.
    //example_helper_function(2000);
    
    //initialize thread, threadData (contains shared counter), mutex object
    pthread_t threadArr[threads];
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
    ThreadData shrd_count;
    shrd_count.count = 1;
    shrd_count.pmtx = &mut;
    shrd_count.verbose = verb;
    shrd_count.max = max;

    int ret = pthread_mutex_init(shrd_count.pmtx, NULL);

    if(ret){
        printf("Error creating mutex\n");
        exit(-1);
    }

    for(int i=0; i<threads; ++i){
            int ret=pthread_create(&threadArr[i],NULL,&pickNext,(void*)&shrd_count);
        if(ret){
            printf("Error creating thread\n");
            exit(-1);
        }
    }

    //wait for the termination of all created threads, and return to the main process
    for(int i=0; i<threads; ++i){
        pthread_join(threadArr[i],NULL);
    }
    
}

