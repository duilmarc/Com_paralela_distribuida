#include <iostream>
#include <mpi.h>

using namespace std;
const int LIMITPINGPONG = 10;

int main()
{
    int comn_sz;
    int my_rank;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comn_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int cont_ping_pong = 0;
    int other_rank = ( my_rank + 1 ) % 2;
    while( cont_ping_pong < LIMITPINGPONG){
        if( cont_ping_pong % 2  == my_rank ){
            cont_ping_pong++;
            MPI_Send(&cont_ping_pong, 1, MPI_INT, other_rank, 0 ,MPI_COMM_WORLD );
            cout<< "Proceso " << my_rank << " enviando al proceso " << other_rank << " el conteo: "<<cont_ping_pong<<endl;
        }
        else{
            MPI_Recv(&cont_ping_pong, 1, MPI_INT, other_rank, 0 ,MPI_COMM_WORLD, MPI_STATUS_IGNORE );
            cout<< "Proceso " << my_rank << " ha recibido del proceso " << other_rank << " el conteo: "<<cont_ping_pong<<endl;
        }
    }
    MPI_Finalize();
    return 0;
}