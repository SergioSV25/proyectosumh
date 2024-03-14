/*
Sergio Sanchiz Villena
Lucas Borges de Castro
Pablo Casimiro Beneitez
*/

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

float Mochila(int M, int n, float *P, float *V, int *objetos)
{
    int i, j, a;
    float **T;

    T = new float* [n+1];
    if (T == NULL)
    {
        cout << "Error al reservar memoria";
        return -1;
    }
    for (a = 0; a <= n; a++)
    {
        T[a] = new float [M+1];
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
                T[i][j] = max(x, y);
            }
        }
    }

    // Mostrar qué objetos se introducen en la mochila
    i = n;
    j = M;
    int num_objetos = 0;
    while (i > 0 && j > 0)
    {
        if (T[i][j] != T[i-1][j])
        {
            objetos[num_objetos] = i;
            num_objetos++;
            j -= P[i];
        }
        i--;
    }

    return T[n][M];
}

/*void leer_archivo(string nombre_archivo, float M, int n, float* P, float *V){
    ifstream archivo_entrada(nombre_archivo);
    if(!archivo_entrada){
        cout<< "Fichero no encontrado o indisponible"<<endl;
    }
    
    // Leemos los dos primeros números del archivo
    archivo_entrada >> M;
    archivo_entrada>> n;  
    
    // Leemos los pesos de los objetos
    P = new float [n+1]; 
    int peso_objeto;
    for (int i = 1; i <= n; i++) {
        archivo_entrada >> peso_objeto;
        P[i]=peso_objeto;
    }
    
    // Leemos los valores de los objetos
    V = new float [n+1];
    int valor_objeto;
    for (int i = 1; i <= n; i++) {
        archivo_entrada >> valor_objeto;
        V[i]=valor_objeto;
    }
    
    // Cerramos el archivo de entrada
    archivo_entrada.close();
}*/

int main()
{
    float *V;
    float *P;
    float M;
    int n;
    float **T;
    int *objetos = new int[n+1];
    string nombre_archivo;
    cout << "Introduce el nombre del archivo a leer: ";
    cin >> nombre_archivo;

    ifstream archivo_entrada(nombre_archivo);
    if(!archivo_entrada){
        cout<< "Fichero no encontrado o indisponible"<<endl;
        return -1;
    }
    
    // Leemos los dos primeros números del archivo
    archivo_entrada >> M;
    archivo_entrada>> n;  
    
    // Leemos los pesos de los objetos
    P = new float [n+1]; 
    int peso_objeto;
    for (int i = 1; i <= n; i++) {
        archivo_entrada >> peso_objeto;
        P[i]=peso_objeto;
    }
    
    // Leemos los valores de los objetos
    V = new float [n+1];
    int valor_objeto;
    for (int i = 1; i <= n; i++) {
        archivo_entrada >> valor_objeto;
        V[i]=valor_objeto;
    }
    
    // Cerramos el archivo de entrada
    archivo_entrada.close();
    
    // Mostramos por pantalla los datos leídos
    cout << "Capacidad maxima de la mochila: " << M << endl;
    cout << "Numero de objetos: " << n << endl;
    cout << "Pesos de los objetos: ";
    for (int i = 1; i <= n; i++) {
        cout << P[i] << " ";
    }
    cout << endl;
    cout << "Valores de los objetos: ";
    for (int i = 1; i <= n; i++) {
        cout << V[i] << " ";
    }
    cout << endl;

    float valor_max = Mochila(M, n, P, V, objetos);
    cout << "Valores maximos que puedes llevar: "<< valor_max <<endl ;

    cout << "Objetos introducidos en la mochila: "<<endl;
    for (int i = 0; i < n; i++)
    {
        if (objetos[i] > 0)
        {
            cout<<i+1<<" objeto ->"<< objetos[i] <<endl;
        }
    }

    return 0;
}
