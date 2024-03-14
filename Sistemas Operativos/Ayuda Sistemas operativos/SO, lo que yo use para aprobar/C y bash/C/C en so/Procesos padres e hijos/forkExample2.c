#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
//Explicacion avanzada en el txt o mas abajo

#define NUM_CHILD 5

int doSomething(void)
{
	int ret;

	srand(getpid());
	ret = (rand() % 256);
	//Generamos un  numero aleatorio

	printf("HIJO: PID = %d, valor aleatorio calculado: %d \n", getpid(), ret);

	return ret;
}

int main(void)
{
	pid_t pidC;
	int status;


	for (int i = 0; i < NUM_CHILD ; ++i)
	{
		//El for esta creando hijos hasta llegar a 5 hijos

		pidC = fork();
		if(pidC > 0)
		{
			continue;
		}
		else if (pidC == 0)
		{
			//El hijo despues de llamar a esta funcion hace exit
			exit(doSomething());
		}	
		else
		{
			//Error
		}	
	}
	//El padre antes de continuar espera a s que sus hijos acaben
	for (int i = 0; i < NUM_CHILD ; ++i)
	{
		//el wait nos va a devolver el identificador del proceso que ha terminado 
		pidC = wait(&status);
		printf("PADRE: PID = %d, hijo de PID = %d terminado, status = %d \n", getpid(), pidC, WEXITSTATUS(status));
	}

	while(1)
	{
		//Como solo sale el padre, se queda en bucle infinito 
		sleep(10);
		printf("zzzzz\n");

	}	


	return 0;
}

/*		**fork, wait y múltiples procesos hijo**

pid_t fork(void);

pid_t wait(int *wstatus)

WEXITSTATUS(wstatus);

*/	
			 							