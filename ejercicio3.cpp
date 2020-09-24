
#include <iostream>
#include <stdio.h>

using namespace std;


void multiplicacion_bloques(int max, int bloque) {

int aMatrix[max][max], bMatrix[max][max], producto[max][max];
// Valores para aMAtrix, bMatrix

    for (int fila = 0; fila < max; fila++)
    {
        for (int columna = 0; columna < max; columna++)
        {
            aMatrix[fila][columna] = rand() % 256;
        }
    }    

    for (int fila = 0; fila < max; fila++)
    {
        for (int columna = 0; columna < max; columna++)
        {
            bMatrix[fila][columna] = rand() % 256;
        }
    }    

    // Multiplicacion por bloque
    for (int i1 = 0; i1 < max/bloque; i1+=bloque)
        for (int j1 = 0; j1 < max/bloque; j1+=bloque)
            for (int k1 = 0; k1 < max/bloque; k1+=bloque)
                for (int i = i1; i<i1+bloque && i<max; i++)                // Multiplicacion normal
                    for (int j = j1; j<j1+bloque && j<max; j++)
                        for (int k = k1; k<k1+bloque && k<max; k++)
                            producto[i][j] += aMatrix[i][k] * bMatrix[k][j];
        
}

int main()
{
    unsigned t0, t1;
    int x = 100;
    for (int iterador = 0; iterador < 5; iterador++) {
        t0=clock();
        multiplicacion_bloques(x,int(x/3));
        t1 = clock();
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "Ejecucion: " << iterador+1 << " - Tiempo de ejecucion: "  << time  << " con un size de " <<x <<endl;
        x *= 1.5;
    }
    return 0;
}