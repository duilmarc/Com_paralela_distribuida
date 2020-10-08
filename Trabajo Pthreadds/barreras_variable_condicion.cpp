#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <ctime> 
using namespace std;


#define BARRIER_COUNT 1
int thread_count;
int count=0;
pthread_cond_t proceed;
pthread_mutex_t barrier_mutex;

void* Thread_work( void* rank);

int main(int argc, char *argv[] ){
    long thread,i;
    pthread_t* thread_handles;
    unsigned t0, t1;
    thread_count = strtol( argv[1], NULL, 10);
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));

    pthread_mutex_init(&barrier_mutex,NULL);
    pthread_cond_init(&proceed,NULL);
    
    t0=clock();
    for(thread = 0; thread < thread_count;thread++)
        pthread_create(&thread_handles[thread], NULL,Thread_work, (void *) thread);
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread],NULL);   
    t1=clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    pthread_mutex_destroy(&barrier_mutex);
    pthread_cond_destroy(&proceed);
    free(thread_handles);
    return 0;
}




void*  Thread_work(void *rank){
    long my_rank = (long) rank;
    int i;

    for( i = 0 ; i < BARRIER_COUNT ; i++)
    {
        pthread_mutex_lock(&barrier_mutex);
        count++;
        if(count == thread_count){
            count = 0;
            cout<<"Thread " << my_rank << " > signalling other threads in barrier "<< i << endl;
            pthread_cond_broadcast(&proceed);
        }
        else
        {
            while(pthread_cond_wait(&proceed, &barrier_mutex)!= 0);
            cout<<"Thread " << my_rank << " > awakened in barrier " << i <<endl;
        }
        pthread_mutex_unlock(&barrier_mutex);
        if(my_rank == 0){
            cout<<" All threads completed barrier "<< i <<endl;
        }
        
    }

    return NULL;
}
