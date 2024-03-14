
#include <unistd.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{

	char *const argv2[] = {"prog2", "abcdef", "ghij", NULL};
	//Vector de argumentos
	//Recordemos que siempre el indice 0 debe ser el rpograma
	// y el resto son mas arguemntos de entrada por poner 
	//pero siempre el ultimo debe de ser null

	printf("%s : %i \n",argv[0], getpid());
	//Con el %s y con el argv[0] imprimimos el nombre del programa
	//Con el %i y el getpid imprmimos el PID del proceso

	execv("./prog2", argv2);
	//Despues de ejecutar esta linea este programa dejara de
	//ejecutarse ya que lo que hace es sustituir el codigo del programa
	//que se esta ejecutando
	//y se le pasara a prog 2 el vector de argumentos como argumento

	printf("ERROR........." );
	//Como despues del execv ya no se ejecuta el codigo restante 
	//el printf y el retunr no ejecutaran a menos que haya un error
	return -1;
}

