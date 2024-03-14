#include <stdlib.h>
#include <iostream>
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

int main() {
    // Pedimos al usuario el número total de procesos
    int procesos;
    int *tiempos_ejecucion;
    int *orden_procesos;

    cout << "Introduce el numero total de procesos: " <<endl;
    cin >> procesos;
    tiempos_ejecucion = new int [procesos+1];
    orden_procesos = new int [procesos+1];

    // Pedimos al usuario los tiempos de ejecución de cada proceso
    for (int i = 0; i < procesos; i++) {
        int tiempo;
        cout << "Introduce el tiempo de ejecucion del proceso " << i+1 << ": "<<endl;
        cin >> tiempo;
        tiempos_ejecucion[i+1] = tiempo;
        orden_procesos[i+1]= tiempo;
    }

    //Vector obtenido
    cout << "Tiempos de ejecucion de los procesos: ";
    for (int i=1; i <=procesos; i++){
        if (i < procesos){
            cout << tiempos_ejecucion[i] << " ";
        }
        else{
            cout << tiempos_ejecucion[i] << endl;
        }
    }

    // Ordenamos los procesos por su tiempo de ejecución
    int izq=1;
    int der=procesos;
    quicksort(tiempos_ejecucion,procesos,izq,der);

    //Orden de ejecucion
    cout << "Orden de ejecucion de los procesos: "<<endl;
    for(int i=1; i<=procesos; i++){
        for(int j= 1; j<=procesos; j++){
            if(tiempos_ejecucion[i]==orden_procesos[j]){
                cout << "Proceso -> " << j <<endl;
            }
        }
    }

    // Calculamos el tiempo total de permanencia en el sistema de todos los procesos
    int tiempo_permanencia_total = 0;
    int tiempo_permanencia_actual = 0;

    for (int i = 1; i <= procesos; i++) {
        tiempo_permanencia_actual += tiempos_ejecucion[i];
        tiempo_permanencia_total += tiempo_permanencia_actual;
    }

    // Mostramos el tiempo mínimo total de permanencia en el sistema de todos los procesos y el orden de ejecución
    cout << endl;
    cout << "El tiempo minimo total de permanencia en el sistema de todos los procesos es " << tiempo_permanencia_total << endl;
    cout << endl;
    return 0;
}