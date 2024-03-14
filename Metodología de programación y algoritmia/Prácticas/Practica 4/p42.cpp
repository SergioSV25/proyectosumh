// Sergio Sanchiz Villena
// Lucas Borges de Castro
// Miguel Aparicio Ferrando

#include <iostream>
#include <stack>

using namespace std;

void binario(int n, stack<int>& pila)
{
    int cociente = n / 2;
    int resto = n % 2;
    pila.push(resto);

    if (cociente == 0)
    {
        return;
    }
    else
    {
        binario(cociente, pila);
    }
}

int main()
{
    int n;
    cin >> n;
    stack<int> pila;
    if(n < 0)
    {
        cout << "-1";
    }
    else
    {
        binario(n, pila);
        for(auto i = pila; !i.empty(); i.pop())
        {
            cout << i.top();
        }
    }
}