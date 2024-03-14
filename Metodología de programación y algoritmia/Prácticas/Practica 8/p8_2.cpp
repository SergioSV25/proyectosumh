#include <iostream>

using namespace std;

float CalcularSuma(int *X, float *V, int k){
    int i;
    float sol = 0;

    for ( i=1 ; i<=k ; i++ ){
        if( X[i]==1 ){
            sol = sol+V[i];
        }
    }
    return sol;
}

void Mochila(float M, int n, float *P, float *V, int *X, int k, int *&Xoptimo, float &voptimo){
    float peso, valor;
    if( k<=n ){
        cout << "K=" << k << " y X= ";
        for(int i=1 ; i<=k ; i++){
            cout << X[i] << " ";
        }
        cout << endl;

        for( int i=0 ; i<=1 ; i++ ){
            X[k] = i;
            peso = CalcularSuma(X,P,k);
            if( peso<=M ){
                if( k==n ){
                    valor = CalcularSuma(X,V,k);
                    if( valor>voptimo ){
                        for( i=1 ; i<=n ; i++ ){
                            Xoptimo[i] = X[i];
                        }
                        voptimo = valor;
                    }

                    /*cout<< "Peso: " << peso << ", ";
                    cout<< "X= (";
                    for(int o = 1; o <= n; o++)
                    {
                        cout << X[o];
                        if(o != n)
                        {
                            cout<< " ";
                        }
                    }
                    cout << ") ";
                    cout << "Voptimo= ";
                    cout << voptimo;
                    cout << endl;*/
                }
                else{
                    Mochila(M,n,P,V,X,k+1,Xoptimo,voptimo);
                }
            }
        }
    }
}

int main()
{
int i, n, *X, k, *Xoptimo;
float *P, *V, M, voptimo;
k=0;
M=10;


//Petición de número de objetos
cout << "Introduce el total de objetos (n):" << endl;
cin >> n;

//Creación de vectores
P = new float [n+1];
if ( P == NULL ){
    cout << "Error al reservar memoria" << endl;
    return -1;
}
V = new float [n+1];
if ( V == NULL ){
    cout << "Error al reservar memoria" << endl;
    return -1;
}
X = new int [n+1];
if ( X == NULL ){
    cout << "Error al reservar memoria" << endl;
    return -1;
}
Xoptimo = new int [n+1];
if ( Xoptimo == NULL ){
    cout << "Error al reservar memoria" << endl;
    return -1;
}

//Petición de pesos y valores
cout << "PESOS:" << endl;
for ( i=1 ; i<=n ; i++ ){
    cout << "Objeto " << i  << ":" << endl;
    cin >> P[i];
    if ( P[i]<0 ){
        cout << "El peso no puede ser negativo" << endl;
        return 0;
    }
}
cout << "VALORES:" << endl;
for ( i=1 ; i<=n ; i++ ){
    cout << "Objeto " << i  << ":" << endl;
    cin >> V[i];
    if ( V[i]<0 ){
        cout << "El valor no puede ser negativo" << endl;
        return 0;
    }
}

cout << endl;
cout << endl;
Mochila(M,n,P,V,X,k,Xoptimo,voptimo);
cout << endl;
cout << endl;

cout << "OBJETOS A INTRODUCIR EN LA MALETA" << endl;
for( i=1 ; i<=n ; i++ ){
    if ( Xoptimo[i]==1 ){
        cout << i << ": " << P[i] << "kg - Valor: " << V[i] << endl;;
    }
}
cout << endl;

float Psol = 0;
for( i=1 ; i<=n ; i++ ){
    if( Xoptimo[i]==1 ){
        Psol = Psol+P[i];
    }
}
cout << "Peso: " << Psol << endl;
cout << "Valor: " << voptimo << endl;
cout << endl;

cout << "OBJETOS QUE QUEDAN FUERA:";
for( i=1 ; i<=n ; i++ ){
    if( Xoptimo[i]==0 ){
        cout << " " << i;
    }
}
cout << endl;

    return 0;
}
