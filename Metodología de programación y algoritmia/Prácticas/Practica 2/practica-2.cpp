// Miguel Aparicio Ferrando
// Lucas Borges de Castro
// Sergio Sanchiz Villena

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Quitar el comentario para ver la traza
//#define TRAZA

void ordenar_asc(int* v, int n)
{
    for(int i = 2; i <= n; i++)
    {
        int x = v[i];
        int j = i - 1;

        #ifdef TRAZA
        cout << "Iteracion i = " << i << ", x = " << x << '\n';
        #endif
        while(j > 0 && v[j] > x)
        {
            #ifdef TRAZA
            cout << '\t' << "Iteracion j = " << j << ", v[j] = " << v[j] << '\n';
            cout << "\t\t" << "v[" << j + 1 << "]" << " pasa a valer " << v[j] << '\n';
            #endif

            v[j+1] = v[j];
            
            #ifdef TRAZA
            cout << "\t\tVector al finalizar la iteracion de j: ";
            for(int t = 1; t <= n; t++)
            {
                cout << v[t] << ' ';
            }
            cout << '\n';
            #endif

            j = j -1;
        }
        v[j+1] = x;

        #ifdef TRAZA
        cout << "\tv[" << j+1 << "]" << " pasa a valer " << x << "\n";  
        cout << "\tVector al finalizar la iteracion de i: ";
        for(int t = 1; t <= n; t++)
        {
            cout << v[t] << ' ';
        }
        cout << '\n';
        #endif
    }
}   

int main()
{
    unsigned long n;
    const int semilla = 10;
    srand(semilla);

    cout << "n: ";
    cin >> n;

    // Vector con valores al azar    
    int* v = new int[n+1];
    for(int i = 1; i <= n ; i++)
    {
        v[i] = rand();
    }

    // Imprimir vector generado
    cout << "Vector generado: ";

    for(int i = 1; i <= 10; i++)
    {
        cout << v[i] << ' ';
    }
    cout << '\n';

    // Ordenar el vector y calcular su tiempo de ejecución
    clock_t inicio;
    clock_t fin;
    double dt;

    inicio = clock();
    ordenar_asc(v,n);
    fin = clock();
    dt = (double)(fin-inicio)/CLOCKS_PER_SEC*1000;

    cout << "Tiempo de ejecucion " << dt << " ms\n";

    // Imprimir vector ordenado
    cout << "Vector ordenado: ";
    for(int i = 1; i <= 10; i++)
    {
        cout << v[i] << ' ';
    }
    cout << '\n';

    // Cáculo del tiempo del caso mejor y caso peor

    int* vmejor = new int[n+1]; // Caso mejor: el vector ya está ordenado de menor a mayor
    int* vpeor = new int[n+1]; // Caso peor: el vector está ordenado de mayor a menor
    for(int i = 1 ; i <= n; i++)
    {
        vmejor[i] = i;
        vpeor[i] = n - i;
    }

    // Cálculo del tiempo de ejecución del caso mejor
    inicio = clock();
    ordenar_asc(vmejor, n);
    fin = clock();
    dt = (double)(fin-inicio)/CLOCKS_PER_SEC*1000;
    cout << "Tiempo del caso mejor: " << dt << " ms\n"; 
    
    // Cálculo del tiempo de ejecución del caso peor
    inicio = clock();
    ordenar_asc(vpeor, n);
    fin = clock();
    dt = (double)(fin-inicio)/CLOCKS_PER_SEC*1000;
    cout << "Tiempo del caso peor: " << dt << " ms\n"; 

    return 0;
}