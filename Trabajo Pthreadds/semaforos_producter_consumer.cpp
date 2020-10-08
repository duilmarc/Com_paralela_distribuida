#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <semaphore.h>
#include <string>
using namespace std;


#define MSG_MAX 100
int thread_count;
void* Send_msage( void* rank);
char ** mensajes;
sem_t* semaphores;


int main(int argc, char *argv[] ){
    long thread;
    pthread_t* thread_handles;
    thread_count = strtol( argv[1], NULL, 10);
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
    mensajes  = (char**) malloc(thread_count*sizeof(char*));
    semaphores = (sem_t*) malloc(thread_count*sizeof(sem_t));
    for(thread = 0; thread < thread_count;thread++)
        pthread_create(&thread_handles[thread], NULL,Send_msage, (void *) thread);
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread],NULL);   
    
    free(thread_handles);
    free(semaphores);
    free(mensajes);
    return 0;
}


void*  Send_msage(void *rank){
    long my_rank = (long) rank;
    long dest = ( my_rank + 1 ) % thread_count;
    
    char* my_msage = (char *) malloc( MSG_MAX*sizeof(char));
    sprintf(my_msage, "Hello to %ld from %ld", dest, my_rank);
    mensajes[dest]= my_msage;
    sem_post(&semaphores[dest]);
    sem_wait(&semaphores[my_rank]);
    cout<< "Thread "<< my_rank << " > " << mensajes[my_rank]<< endl;
    return NULL;
}

