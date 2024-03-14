/*
Sergio Sanchiz Villena
Lucas Borges de Castro
Pablo Casimiro Beneitez
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

float maximo(float x, float y)
{
    if (x > y)
    {
        return x;
    }
    else 
    {
        return y;
    }
}

float Mochila(int M, int n, float *P, float *V)
{
    int i, j, a;
    float **T;

    T = new float* [n];
    if (T == NULL)
    {
        cout << "Error al reservar memoria";
        return -1;
    }
    for (a = 0; a <= n; a++)
    {
        T[a] = new float [M];
        if (T[a] == NULL)
        {
            cout << "Error al reservar memoria";
            return -1;
        }
    }

    for (i = 0; i <= M; i++)
    {
        T[0][i] = 0;
    }
    for (i = 0; i <= n; i++)
    {
        T[i][0] = 0;
    }

    for (i=1; i<=n; i++)
    {
        for(j=1; j<=M; j++)
        {
            if (P[i] > j)
            {
                T[i][j] = T[i-1][j];
            }
            else
            {
                int z = j-P[i];
                float x = T[i-1][j];
                float y = V[i] + T[i-1][z];
                T[i][j] = maximo(x, y);

            }
        }
    }

    return T[n][M];
}

void leerArchivo(float *V, float *P, int &n, float &M, string nombreArchivo){
    ifstream archivo(nombreArchivo.c_str());
    if (archivo.is_open()){
        archivo >> M;
        archivo >> n;

        for (int t = 1; t <= n; t++)
        {
            archivo >> P[t];
        }

        for (int x = 1; x <=n; x++)
        {
            archivo >> V[x];
        }

        archivo.close();
    }
    else{
        cout << "No se pudo abrir el archivo." << endl;
    }
}

int main()
{
    float *V;
    float *P;
    float M;
    int n;
    string nombreArchivo;

    //Pedir nombre del archivo
    cout << "Introduce el nombre del archivo: ";
    cin >> nombreArchivo;

    //Creacion y comprobación de vectores de pesos y valores
    P = new float [n+1];
    if (P == NULL)
    {
        cout << "Error al reservar memoria." << endl;
        return -1;

    }

    V = new float [n+1];
    if (V == NULL)
    {
        cout << "Error al reservar memoria." << endl;
        return -1;
        
    }

    //Leer archivo
    leerArchivo(V, P, n, M, nombreArchivo);

    cout << "Valores maximos que puedes llevar: "<< Mochila(M, n, P, V);

    return 0; 

}
