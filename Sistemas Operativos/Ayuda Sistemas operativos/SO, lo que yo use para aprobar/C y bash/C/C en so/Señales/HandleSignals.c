#include <stdio.h>
#include <signal.h>
#include <unistd.h>
//Explicacion avanzada en el txt o mas abajo


MySignalHandler(int sig)
{
	printf("Signal numer is %d \n", sig);
}

int main(void)
{
	signal(SIGIO, &MySignalHandler);
	//Esta signal es un trap, es decir, cuando se reciba la señal SIGIO
	//Llamara al segundo argumento, es decir, la funcion MySignalHandler y la ejecutara.
	while(1)
	{
		printf("zzzZZZzzz\n");
		sleep(2);
	}	

	return 0;
}

/*		**Signals (señales)

- Que es una señal
- Envío de una señal
- Tratar una señal (programa en C)

Comandos: kill, ps
Función:  sighandler_t signal(int signum, sighandler_t handler);
*/	
			 							