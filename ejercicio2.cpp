#include <iostream>
#include <ctime> 
 
using namespace std;
void multiplicacion(int max) {
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
    

    for (int fila = 0; fila < max; fila++) {
        for (int columna = 0; columna < max; columna++) {
            for (int interna = 0; interna < max; interna++) {
                producto[fila][columna] += aMatrix[fila][interna] * bMatrix[interna][columna];
            }
        }
    }
}


int main()
{
    unsigned t0, t1;
    int x = 100;
    for (int iterador = 0; iterador < 5; iterador++) {
        t0=clock();
        multiplicacion(x);
        t1 = clock();
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "Ejecucion: " << iterador+1 << " - Tiempo de ejecucion: "  << time  << " con un size de " <<x <<endl;
        x *= 1.5;
    }
    return 0;
}