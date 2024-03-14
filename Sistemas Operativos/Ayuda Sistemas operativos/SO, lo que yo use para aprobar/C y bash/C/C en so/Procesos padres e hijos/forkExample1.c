#include<unistd.h>
#include <stdio.h>
//Explicacion avanzada en el txt o mas abajo
int main(void)
{
	int var = 22;
	pid_t pidC;
	printf("** proc padre: . PID = %d comienza ** \n", getpid());
	pidC = fork();//SE hace una llamada al sistema para crear otro proceso
	//se crea un copia del proceso padre
	//El fork() no solo crea el proceso hijo sino que retona un valor entero
	//si ese valor es mayor que 0 sabemos que es el padre(el padre siempre retorna el pid del hijo)
	// si ese valor es 0 es el hijo
	printf("** proc. PID = %d, mi hijo es: pidC = %d ejecutandose ** \n", getpid(), pidC);

	if(pidC > 0)
	{
		var = 44;
	}
	else if (pidC == 0)
	{
		var = 33;
	}
	else
	{
		printf("Error");
	}	

//Todo se ejecutara 2 veces 1 por el padre y otra por el hijo
	while(1)
	{

		sleep(2);
		printf("** proc. PID = %d, var = %d ejecutandose ** \n", getpid(), var);
	}


}

/*		**fork(). Proceso padre, hijo, huérfano, zombie**

pid_t fork(void)
	- Crea un nuevo proceso ("hijo")
	- El proceso hijo es un dupliacdo del "padre"
	- Los dos procesos:
						- Tienen PIDs diferentes
						- Corren en espacios de memoria separados

Retorno de fork()
	> Si todo va bien:
						- retorno del padre: PID del hijo
						- retorno al hijo:   0
	> Si hay errores: 	
					 	- retorno al padre: -1
					 	(el hijo no es creado) 

*/	


/*	
Para poder ver los procesos nos vamos a la consola y ponemos ps lf
ahi poodremos ver dos columnas, una que es PID (que son los pids)
y otra que es ppid que son los padres de los procesos, si nos 
fijamos veremos que el ppid del proceso hijo es el pid del padres

si en la consola matamos al proceso padre el hijo se seguira ejecutando pero 
su ppid sera distinto, ese ppid sera su nuevo padre, por si queremos 
saber cual es su padre ponemos en consola ps lp (y el pid) y nos mostrara 
que proceso tiene ese pid
En el caso de que matemos al hijo si nos fijamos en los procesos saldra
(nombre del proceso ) <defunct> es decir, es un proceso zombie, ya que en la 
columna stat esta z+

*/				 							