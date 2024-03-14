// Sergio Sanchiz Villena
// Lucas Borges de Castro
// Miguel Aparicio Ferrando

#include <iostream>
#include <stack>

using namespace std;

int impar(int n)
{
    return n & 1 ? 1 : 0;
}

int p43_recursiva(int x, int n)
{
    int r;
    if(n == 0)
    {
        r = 1;
    }
    else
    {
        if(impar(n))
        {
            r = x*p43_recursiva(x, n-1);
        }
        else
        {
            r = p43_recursiva(x, n/2);
            r = r * r;
        }
    }

    return r;
}

int p43_iterativa(int x, int n)
{
    int x1 = x;
    int n1 = n;
    stack<int> pila;

    while(n1 != 0)
    {
        if(impar(n1))
        {
            pila.push(n1);
            n1 = n1 - 1;
        }
        else
        {
            pila.push(n1);
            n1 = n1/2;
        }
    }

    int r = 1;

    while(!pila.empty())
    {
        n1 = pila.top();
        pila.pop();

        if(impar(n1))
        {
            r = x * r;
        }
        else
        {
            r = r * r;
        }

    }

    return r;
}

int main()
{
    int x,n;
    cout << "x: ";
    cin >> x;
    cout << "n: ";
    cin >> n;

    if(n < 0) 
    {
        cout << "Error";
    }
    else
    {
        cout << "Resultado de la versión recursiva: " << p43_recursiva(x,n) << '\n';
        cout << "Resultado de la version iterativa: " << p43_iterativa(x,n) << '\n';
    }

    return 0;
}