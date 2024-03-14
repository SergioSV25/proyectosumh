#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

    //ALUMNOS:
    //Lucas Borges de Castro
    //Pablo Casimiro Beneitez
    //Sergio Sanchiz Villena

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

   //if(estrategia==1){

        //MEDIANA DE ELEMENTO DEL MEDIO,PRIMERO Y ÚLTIMO
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
    //}

    /*if(estrategia==2)
    {
    //ELEMENTO DEL FINAL
    sol = der;
    }

    if(estrategia==3)
    {
     //ELEMENTO ALEATORIO
        sol = izq ;
    }*/
    return sol;
}



void quicksort(int *V,int n,int izq,int der/*, int estrategia*/){
int i,d,p;
    int pivote;
    p=seleccionar_pivote(V,n,izq,der/*,estrategia*/);

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
        quicksort(V,n,izq,d/*,estrategia*/);
    }
    if (i<der){
        quicksort(V,n,i,der/*,estrategia*/);
    }
}

int main(){
    //CREACIÓN DE VECTOR//

    int n;
    int *V;

	//PARÁMETROS DE ENTRADA-SALIDA//

    cout << "Introduce numero total elementos del vector:" << endl;
    cin>>n;
    V = new int [n+1];

    if ( V == NULL ){
        cout << "Error al reservar memoria" << endl;
        return -1;
    }

    int x;
    srand(time(NULL));
    for (x=1;x<=n;x++){
        //cout << "Introduce elemento " << x <<":" << endl;
        //cin>>V[x];
            V[x] = rand();
    }
    
    /*
    int estrategia;
    cout<<"Estrategia del pivote (1, 2, 3):" <<endl;
    cin>>estrategia;
    */

    

    int izq=1;
    int der=n;

    cout << "Vector original: ";
    for (int i=1; i <=n; i++){
        if (i < n){
            cout << V[i] << " ";
        }
        else{
            cout << V[i];
        }
    }
    cout << endl;

    clock_t tinicio, tfin;
    double tiempo;
    tinicio = clock();
    quicksort(V,n,izq,der/*,estrategia*/);
    tfin = clock();

    cout << "Vector ordenado: ";
    for (int i=1; i <=n; i++){
        if (i < n){
            cout << V[i] << " ";
        }
        else{
            cout << V[i];
        }
    }
    cout << endl;

    tiempo = (double)(tfin-tinicio) / CLOCKS_PER_SEC * 1000;
    cout << "Tiempo: " << tiempo << endl;

    return 0;
}