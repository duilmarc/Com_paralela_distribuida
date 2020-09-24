#include <iostream>
#include <ctime> 

#define MAX 512
using namespace std;

void Problem1(int max) {
    unsigned t0, t1;
    double A[max][max], x[max], y[max];
    srand(time(NULL));
    /* 
        Generacion de A
    */
    for (int fila = 0; fila < max; fila++)
    {
        for (int columna = 0; columna < max; columna++)
        {
            A[fila][columna] = rand() % 256;
        }
    }
    /* 
        Generacion de x
    */
    for (int columna = 0; columna < max; columna++)
    {
        x[columna] = rand() % 256;

    }
    /* 
        Seteamos y
    */
    for (int columna = 0; columna < max; columna++)
    {
        y[columna] = 0;
    }
    // ................................................... 2 for
    t0=clock();
    for ( int fila = 0; fila < max ; fila++)
        for ( int columna= 0; columna< max ; columna++)
            y[fila] += A[fila][columna]*x[columna];

    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo de ejecucion 1 : " << time << endl;
    // ................................................... 2 for
    
    /* 
        Seteamos y
    */
    for (int columna = 0; columna < max; columna++)
    {
        y[columna] = 0;
    }
    t0=clock();

    for ( int columna= 0; columna< max ; columna++)
        for ( int fila = 0; fila < max ; fila++)
            y[fila] += A[fila][columna]*x[columna];

    t1 = clock();
    time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo de ejecucion 2 : " << time << endl;
}

int main()
{
    int x = 100;
    for (int iterador = 0; iterador < 6; iterador++) {
        cout << "Ejecucion: " << iterador+1 << " con un size de " <<x <<endl;
        Problem1(x);
        x *= 1.5;
    }
   
    return 0;
}