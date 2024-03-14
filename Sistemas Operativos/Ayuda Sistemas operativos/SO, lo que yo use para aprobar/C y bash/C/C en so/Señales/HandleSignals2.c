#include <stdio.h>
#include <signal.h>
#include <unistd.h>
//Explicacion avanzada en el txt o mas abajo


MySignalHandler(int sig)
{
	printf("Señal recibida valor %d \n", sig);
}

int main(void)
{
	

	signal(SIGALRM, SIG_IGN);
	//En este caso de segundo argumento le pasamos SIG_IGN, IGN= ignore
	//esto lo sabemos porque lo pone en el man signal , es decir, si quiero terminarlo
	//pondria SIG_TERM
	signal(SIGALRM, &MySignalHandler);
	while(1)
	{
		printf("....Esperando a recibir señales....\n");
		sleep(2);
	}	

	return 0;
}

/*		**Signals II: comprotamiento por defecto** 
					(Signal dispositions)

- Comportamiento por defecto (cuando la señal no es atendida)
- Ignorar una señal

Comandos: kill, ps
Función:  sighandler_t signal(int signum, sighandler_t handler);
*/	
			 							