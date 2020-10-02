
#include <mpi.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>     

using namespace std;


void Generate_matrix( double local_A[], int local_m , int local_n ) {
   int i, j;
   for (i = 0; i < local_m; i++)
      for (j = 0; j < local_n; j++) 
         local_A[i*local_n + j] = ((double) random())/((double) 256);
}  /* Generate_matrix */


void generar_vector(double x[], int n) {
    for(register int i = 0; i < n; i++)
        x[i] = ((double)random()) / ((double)256);
}

void mult( double local_A[], double local_x[], double local_y[], int local_m, int n, int local_n, MPI_Comm comm)
{
    double* x; 
    int local_i, j;
    x = (double*) malloc( n * sizeof(double));
    MPI_Allgather( local_x, local_n, MPI_DOUBLE, x, local_n, MPI_DOUBLE, comm);
    for(local_i = 0; local_i < local_m; local_i++)
    {
        local_y[local_i] = 0.0;
        for(j = 0 ; j < n ; j++)
        {
            local_y[local_i] += local_A[local_i*n+j]*x[j];
        }
    }
    free(x);
}

void asignar_dimensiones(
      int*      m_p       , 
      int*      local_m_p ,
      int*      n_p       ,
      int*      local_n_p ,
      int       my_rank   ,
      int       comm_sz   ,
      MPI_Comm  comm      ) {

   if (my_rank == 0) {
      *m_p = 16384;
      *n_p = 16384;
   }
   MPI_Bcast(m_p, 1, MPI_INT, 0, comm);
   MPI_Bcast(n_p, 1, MPI_INT, 0, comm);
   *local_m_p = *m_p/comm_sz;
   *local_n_p = *n_p/comm_sz;
}  

void separar_memoria( double**  local_A_pp, double**  local_x_pp ,double**  local_y_pp, int local_m, int n, int local_n, MPI_Comm comm ) {
   *local_A_pp = (double*) malloc(local_m*n*sizeof(double));
   *local_x_pp = (double*) malloc(local_n*sizeof(double));
   *local_y_pp = (double*) malloc(local_m*sizeof(double));
}  

int main() {

   double* local_A;
   double* local_x;
   double* local_y; 
   int local_m , m ; 
   int local_n ,n ;
   int my_rank, comm_sz;
   double inicio, fin, tiempo_local, tiempo_demorado;
   MPI_Comm  comm;

   MPI_Init(NULL, NULL);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   asignar_dimensiones(&m, &local_m, &n, &local_n, my_rank, comm_sz, comm );
   separar_memoria(&local_A, &local_x, &local_y, local_m, n, local_n, comm);
   Generate_matrix(local_A, local_m, n);
   generar_vector(local_x, local_n);
  
   MPI_Barrier(comm);
   inicio = MPI_Wtime();
   mult(local_A, local_x, local_y, local_m, n, local_n, comm);
   fin = MPI_Wtime();
   tiempo_local = fin-inicio;
   MPI_Reduce(&tiempo_local, &tiempo_demorado, 1, MPI_DOUBLE, MPI_MAX, 0, comm);

   if (my_rank == 0)
      cout<<"tiempo transcurrido: "<< tiempo_demorado << endl;

   free(local_A);
   free(local_x);
   free(local_y);
   MPI_Finalize();      
   return 0;
}  
