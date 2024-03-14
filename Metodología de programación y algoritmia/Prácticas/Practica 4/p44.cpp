// Sergio Sanchiz Villena
// Lucas Borges de Castro
// Miguel Aparicio Ferrando

#include <iostream>
#include <stack>

using namespace std;

int p44_recursiva(int x, int y) 
{
  	if (x <= 4) 
	{
		return x + y;
  	} 
	else 
	{
    	x = x - 4;
    	y = y / 3;
    	return p44_recursiva(x, y) + x * y;
	}
}

int p44_iterativa(int x, int y) 
{
	int x1 = x;
	int y1 = y;
	stack<int> pila_x;
	stack<int> pila_y;

	while (!(x1 <= 4)) 
	{
		x1 = x1 - 4;
		y1 = y1 / 3;
		pila_x.push(x1);
		pila_y.push(y1);
	}

	int resultado = x1 + y1;


	while (!pila_y.empty()) 
	{
		x1 = x1 + 4;
		x1 = pila_x.top();
		y1 = pila_y.top();
		pila_x.pop();
		pila_y.pop();
		resultado = resultado + x1 * y1;
	}

	return resultado;
}

int main() {
  int x, y;
  cout << "x: ";
  cin >> x;
  cout << "y: ";
  cin >> y;

  cout << "Resultado de la versión recursiva: " << p44_recursiva(x, y) << '\n';
  cout << "Resultado de la versión iterativa: " << p44_iterativa(x, y) << '\n';

  return 0;
}