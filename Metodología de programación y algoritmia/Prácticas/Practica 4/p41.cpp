#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


int combinaciones_traza(int n, int k, int tabs=0){
    static int llamadas = 1;
    cout <<string(tabs,'\t') << llamadas <<".-combinaciones_traza(" << n <<", "<< k <<")"<<endl;
    llamadas++;
    if(k==n || k==0){
        return 1;
    }else{
        return combinaciones_traza(n-1,k-1,tabs+1) + combinaciones_traza(n-1,k,tabs+1);
    }
}   

int main()
{
    int n,k;

    cout << "Valor de N: ";
    cin >> n;
    cout << "Valor de K: ";
    cin >> k;
    
    combinaciones_traza(n,k);
   
    return 0;
}

