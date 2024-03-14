
#include <unistd.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
	printf("%s : %i \n",argv[0], getpid());
	//Con el %s y con el argv[0] imprimimos el nombre del programa
	//Con el %i y el getpid imprmimos el PID del proceso

	for (int i = 0; i < argc; ++i)
	{
		printf("Argumento %d, %s\n",i, argv[i] );
		//Arguemnto %d indica la cantidad de argumentos
		//%s argv[i] el programa en cuestion
		//Digo esto ya que es un bucle for y hara tantas iteraciones 
		//como argumentos se le pase
	}
	return 0;
}
