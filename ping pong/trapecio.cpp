#include <mpi.h>
#include <iostream>
#include <math.h>
using namespace std;

double funcion(double valor){
    return 10*sin(valor);
}

double trapezoide( double a, double b, double h, int trap_count)
{
    double estimado, x;
    int i;
    estimado = ( funcion(a) + funcion(b)) / 2.0;
    for( i = 1 ; i <= trap_count -1 ; i++)
    {
        x = a + i*h;
        estimado += funcion(x); 
    }
    estimado = estimado*h;
    return estimado;
}
int main()
{
    int comn_sz;
    int my_rank;
    int n= 1024, local_n; // cantidad de cuadrados
    double a = 1.0 ,b= 3.0, local_a, local_b, h;  // limites locales y globales
    h = abs( b - a )/ 2;
    double local_x_proces, total_x_proce;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comn_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // Asignacion a cada procesador de los espacios que calcularan
    local_n = n/comn_sz; // cantidad de n asignados a cada procesador
    local_a = a + my_rank+local_n*h;
    local_b = local_a + local_n*h;
    local_x_proces = trapezoide( local_a,local_b, h ,local_n);
    if(my_rank == 0)
    {
        total_x_proce = local_x_proces;
        for( int proc =  1 ; proc < comn_sz ; proc++)
        {
            MPI_Recv(&local_x_proces, 1, MPI_DOUBLE, proc, 0 ,MPI_COMM_WORLD, MPI_STATUS_IGNORE );
            total_x_proce += local_x_proces;
        }
    }
    else
    {
       MPI_Send(&local_x_proces, 1, MPI_DOUBLE, 0 , 0 , MPI_COMM_WORLD);
    }
    if(my_rank == 0)
    {
        cout<< "Con un total de " << n << " trapezoides y un total de "<< comn_sz << " procesadores, el calculo estimado: "<<endl;
        cout<< total_x_proce<<endl;
    }
    MPI_Finalize();
    return 0;
}