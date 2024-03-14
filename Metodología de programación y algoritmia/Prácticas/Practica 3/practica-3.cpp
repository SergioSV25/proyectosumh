// Sergio Sanchiz Villena
// Lucas Borges de Castro
// Miguel Aparicio Ferrando

#include <iostream>

int espar(int n)
{
    return n & 1 ? 0 : 1;
}

int potencia2(int a, int b)
{
    if(b == 0)
    {
        return 1;
    }
    
    int s = potencia2(a, b/ 2);
    if (espar(b))
    {
        return s * s;
    }
    else
    {
        return a * s * s;
    }
}

int potencia2traza(int a, int b)
{
    static int llamadas = 1;
    if(b == 0)
    {
        return 1;
    }
    
    if (llamadas != 1) std::cout << std::string(llamadas, '\t');

    std::cout << llamadas << ". - potencia2(" << a << "," << b << ")\n";
    llamadas++;

    int s = potencia2traza(a, b/ 2);
    if (espar(b))
    {
        return s * s;
    }
    else
    {
        return a * s * s;
    }
}

int main()
{
    //Base
    int a;
    //Exponente
    int b;
    std::cout << "Ingresa el valor de la base: " << std::endl;
    std::cin >> a;
    std::cout << "Ingresa el valor de la potencia: " << std::endl;
    std::cin >> b;
    std::cout << potencia2(a,b);
}