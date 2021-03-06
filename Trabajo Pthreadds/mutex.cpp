#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime> 
 
using namespace std;

int thread_count;
int n; 
int flag;
double sum;
void* Thread_Sum( void* rank);
double serial_pi( int n);
pthread_mutex_t mutex;

int main(int argc, char *argv[] ){
    long thread;
    unsigned t0, t1;
    pthread_t* thread_handles;
    thread_count = strtol( argv[1], NULL, 10);
    n = strtol( argv[2], NULL, 10);
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
    sum = 0.0;
    pthread_mutex_init(&mutex, NULL);
    t0=clock();
    for(thread = 0; thread < thread_count;thread++)
        pthread_create(&thread_handles[thread], NULL,Thread_Sum, (void *) thread);
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread],NULL);   
    t1=clock();

    sum *= 4.0;
    
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout.precision(17);
    cout << "Execution Time: " << time << endl;
    pthread_mutex_destroy(&mutex);
    free(thread_handles);
    return 0;
}

double serial_pi( int n ){
    double suma = 0.0;
    double factor = 1.0;
    for(int i = 0 ; i < n ; i++, factor = -factor)
        suma += factor/ (2*i+1);
    return 4.0*suma;
}


void*  Thread_Sum(void *rank){
    long my_rank = (long) rank;
    double factor, local_sum = 0.0;
    int i;
    int my_n = n/thread_count;
    int my_first_i = my_n*my_rank;
    int my_last_i = my_first_i + my_n;

    if(my_first_i % 2 == 0 )
        factor = 1.0;
    else
    {
        factor = -1.0;
    }
    for ( i = my_first_i ; i < my_last_i; i++, factor = -factor){
        local_sum += factor/( 2 * i +1 );
    }
    pthread_mutex_lock(&mutex);
    sum += local_sum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

