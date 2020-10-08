#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <ctime> 
using namespace std;


#define BARRIER_COUNT 1
int thread_count;
int barrier_thread_count[BARRIER_COUNT];
pthread_mutex_t barrier_mutex;

void* Thread_work( void* rank);



int main(int argc, char *argv[] ){
    long thread,i;
    pthread_t* thread_handles;
    unsigned t0, t1;
    thread_count = strtol( argv[1], NULL, 10);
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));

    for ( i = 0; i < BARRIER_COUNT; i++) barrier_thread_count[i] = 0;
    pthread_mutex_init(&barrier_mutex,NULL);
    
    t0=clock();
    for(thread = 0; thread < thread_count;thread++)
        pthread_create(&thread_handles[thread], NULL,Thread_work, (void *) thread);
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread],NULL);   
    t1=clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    pthread_mutex_destroy(&barrier_mutex);
    free(thread_handles);
    return 0;
}


void*  Thread_work(void *rank){
    long my_rank = (long) rank;
    int i;

    for( i = 0 ; i < BARRIER_COUNT ; i++)
    {
        pthread_mutex_lock(&barrier_mutex);
        barrier_thread_count[i]++;
        pthread_mutex_unlock(&barrier_mutex);
        while( barrier_thread_count[i]< thread_count);
        if(my_rank == 0){
            cout<<" All threads completed barrier "<< i <<endl;
        }
        
    }

    return NULL;
}

