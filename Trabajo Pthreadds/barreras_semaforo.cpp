#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <semaphore.h>
#include <string>
#include <ctime> 
using namespace std;


#define BARRIER_COUNT 100
int thread_count;
int counter;

sem_t barrier_sem[BARRIER_COUNT];
sem_t count_sem;

void* Thread_work( void* rank);



int main(int argc, char *argv[] ){
    long thread,i;
    pthread_t* thread_handles;
    unsigned t0, t1;
    thread_count = strtol( argv[1], NULL, 10);
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
    for ( i = 0; i < BARRIER_COUNT; i++) sem_init(&barrier_sem[i],0,0);
    sem_init(&count_sem, 0,1);
    t0=clock();
    for(thread = 0; thread < thread_count;thread++)
        pthread_create(&thread_handles[thread], NULL,Thread_work, (void *) thread);
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread],NULL);   
    t1=clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    sem_destroy(&count_sem);

    for ( i = 0; i < BARRIER_COUNT; i++) sem_destroy(&barrier_sem[i]);
    free(thread_handles);
    return 0;
}


void*  Thread_work(void *rank){
    long my_rank = (long) rank;

    int i, j;

    for( i = 0 ; i < BARRIER_COUNT ; i++)
    {
        sem_wait(&count_sem);
        if(counter == thread_count - 1){
            counter = 0;
            sem_post(&count_sem);
            for(j= 0 ; j < thread_count - 1 ; j++ )
                sem_post(&barrier_sem[i]);
        }
        else
        {
            counter++;
            sem_post(&count_sem);
            sem_wait(&barrier_sem[i]);
        }
        if(my_rank == 0){
            cout<<" All threads completed barrier "<< i <<endl;
        }
        
    }

    return NULL;
}

