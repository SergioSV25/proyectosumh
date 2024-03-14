#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>

using namespace std;


void intercambiar(int *V,int& i,int& d)
{
    int aux;

    aux=V[i];
    V[i]=V[d];
    V[d]=aux;
}

int seleccionar_pivote(int *V, int n, int izq, int der/*, int estrategia*/){
    int i, d, m, sol;
    i = izq;
    d = der;
    m = n/2;

    if((V[m]<=V[d])&&(V[m]>=V[i])){
        sol = m;
    }
    else if((V[m]<=V[i])&&(V[m]>=V[d])){
        sol = m;
    }
    else if((V[d]<=V[m])&&(V[d]>=V[i])){
        sol = d;
    }
    else if((V[i]<=V[m])&&(V[i]>=V[d])){
        sol = i;
    }
    else if((V[d]<=V[i])&&(V[d]>=V[m])){
        sol = d;
    }
    else if((V[i]<=V[d])&&(V[i]>=V[m])){
        sol = i;
    }

    return sol;
}

void quicksort(int *V,int n,int izq,int der){
int i,d,p;
    int pivote;
    p=seleccionar_pivote(V,n,izq,der);

    if (p>0){
        pivote=V[p];
        i=izq;
        d=der;
        while (i<=d){
            while (V[i]<pivote){
                i=i+1;
            }
            while (V[d]>pivote){
                d=d-1;
            }
            if (i<=d){
                intercambiar(V,i,d);
                i=i+1;
                d=d-1;
            }
        }
    }
    if (izq<d){
        quicksort(V,n,izq,d);
    }
    if (i<der){
        quicksort(V,n,i,der);
    }
}

void leerFichero( int* tiempos_ejecucion, int* orden_procesos, int &n){
    ifstream fDatos;
    int i;
    char linea[200], *tok;
    //Abrir fichero
    string nombre_archivo;
    cout << "Introduce el nombre del archivo de entrada: " <<endl;
    cin >> nombre_archivo;
    fDatos.open (nombre_archivo);

    //Lectura primera linea -- Procesos
    fDatos.getline(linea, 200);
    tok=strtok (linea, " \t\r\n");
    n = atoi (tok);
    tiempos_ejecucion = new int [n+1];
    orden_procesos = new int [n+1];
    cout<<"leo la primera linea";

    //Lectura segunda linea -- Tiempos
    fDatos.getline(linea, 200);
    tok=strtok (linea, " \t\r\n");
    i = 1;
    tiempos_ejecucion[i] = atoi(tok);
    orden_procesos[i] = atoi(tok);
    for (i = 2; i<=n; i++)
    {
        tok= strtok (NULL, " \t\r\n");
        tiempos_ejecucion[i] = atoi(tok);
        orden_procesos[i] = atoi(tok);
    }
    cout<<"leo la segunda linea";

    //Cerrar archivo
    fDatos.close();
}

int main() {
    int n, i;
    int *tiempos_ejecucion;
    int *orden_procesos;
    int *vector;
    ifstream fDatos;
   
    //lectura de ficheros
    leerFichero(tiempos_ejecucion,orden_procesos, n);
    cout<<n;

    //Vector obtenido
    cout << "Tiempos de ejecucion de los procesos: ";
    for (int i=1; i <=n; i++){
        if (i <= n){
            cout << tiempos_ejecucion[i] << " ";
        }
        else{
            cout << tiempos_ejecucion[i] << endl;
        }
    }

    // Ordenamos los procesos por su tiempo de ejecución
    int izq=1;
    int der=n;
    quicksort(tiempos_ejecucion,n,izq,der);

    //Orden de ejecucion
    cout << "Orden de ejecucion de los procesos: "<<endl;
    for(int i=1; i<=n; i++){
        for(int j= 1; j<=n; j++){
            if(tiempos_ejecucion[i]==orden_procesos[j]){
                cout << "Proceso -> " << j <<endl;
            }
        }
    }

    // Calculamos el tiempo total de permanencia en el sistema de todos los procesos
    int tiempo_permanencia_total = 0;
    int tiempo_permanencia_actual = 0;

    for (int i = 1; i <= n; i++) {
        tiempo_permanencia_actual += tiempos_ejecucion[i];
        tiempo_permanencia_total += tiempo_permanencia_actual;
    }

    // Mostramos el tiempo mínimo total de permanencia en el sistema de todos los procesos y el orden de ejecución
    cout << endl;
    cout << "El tiempo minimo total de permanencia en el sistema de todos los procesos es " << tiempo_permanencia_total << endl;
    cout << endl;
    return 0;
}