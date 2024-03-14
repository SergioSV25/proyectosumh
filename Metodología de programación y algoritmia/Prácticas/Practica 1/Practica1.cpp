#include <iostream>

using namespace std;

int Contar(int V[], int x, int n){
    int i, nveces;
    nveces = 0;

    for ( i = 1; i <= n; i++)
    {
        if(V[i] == x){
            nveces++;
        }
    }
    return nveces;
}

int main()
{
    int x, n;

    //PASO 1.1
    cout << "Introduce el valor de x: "; //Valor que se busca
    cin >> x;

    cout << "Introduce el valor de n: "; //Tamanyo del array
    cin >> n;

    //PASO 1.2
    int *vpeor;
    int *vmejor;
    int *vcualquiera;
    vpeor = new int[n+1];
    vmejor = new int[n+1];
    vcualquiera = new int[n+1];
    
    //Caso PEOR
    int i;
    for(int i = 1; i <= n; i++){
        vpeor[i] = x;
    }
    
    cout << "vpeor: ";
    for ( i = 1; i <= n; i++)
    {
        cout << vpeor[i] << " ";
    }
    //Llamo a funcion Contar con el parametro del array peor
    int numeroveces = Contar(vpeor, x, n);
    //Imprimo el resultado de la funcion
    cout << "\nEl numero de veces que aparece " << x << " son: " << numeroveces << " \n";

    //Caso MEJOR
    int j;
    for(j = 1; j <= n; j++){
        vmejor[j] = x+1;
    }

    cout << "\nvmejor: ";
    for(j = 1; j <= n; j++){
        cout << vmejor[j] << " ";
    }
    //Llamo a funcion Contar con el parametro del array mejor
    numeroveces = Contar(vmejor, x, n);
    //Imprimo el resultado de la funcion
    cout << "\nEl numero de veces que aparece " << x << " son: " << numeroveces << " \n";

    //Caso CUALQUIERA
    int z;
    for(z = 1; z <= (n/2); z++){
        vcualquiera[z] = x;
    }
    for(z = ((n/2)+1); z <= n; z++){
        vcualquiera[z] = x+1;
    }
    
    cout << "\nvcualquiera: ";
    for (z = 1; z <= n; z++){
        cout << vcualquiera[z] << " ";
    }
    
    //Llamo a funcion Contar con el parametro del array cualquiera
    numeroveces = Contar(vcualquiera, x, n);
    //Imprimo el resultado de la funcion
    cout << "\nEl numero de veces que aparece " << x << " son: " << numeroveces << " \n";

    return 0;
}
