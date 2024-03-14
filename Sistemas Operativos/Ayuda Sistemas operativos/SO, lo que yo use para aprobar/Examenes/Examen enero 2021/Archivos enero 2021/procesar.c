#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "func.h"
#include "sem.h"

#define SSEED 99

//Programa principal
int main( int argc, char *argv[] )
{
	struct sigaction action;
	int status;
	char buffer[100];

	int i,c;       
	int pid;    
	int carga=0; 

	int numJobs;
	int maxCarga=100;
	int maxJobs=100;
	int maxChilds=26;
	int h; 
	int jobs;

	char theChar;

	char jobsFilePath[100]="./jobsfile.txt";
	char countsFilePath[100]="./jobscount.txt";

	//TODO-BEGIN-------------------------
		//Inicializamos la semilla para la generacion de aleatorios

		srand(getpid());

	//TODO-END-------------------------

	//Inicializamos las condicion de permanencia en bucle de los hijos.
	doContinue=true;

	//Control de paraḿetros
	//TODO-BEGIN-------------------------
		//Controlamos el numero de parametros.
		//Si error mostramos mensaje, sintaxis y terminamos con -1
		if(argc !=3)
		{
			printf("Error en el numeor de parametros introducidos");
			sintaxis();
			exit(-1);
		}
	//TODO-END-------------------------

	//Capturamos el numero de hijos que procesarán y el numero de Jobs
	numHijos=atoi(argv[1]);
	numJobs=atoi(argv[2]);


	//TODO-BEGIN-------------------------
		//Control del número de hijos
		//Valores validos entre 1 y maxChilds
		//Si error mostramos mensaje, sintaxis y terminamos con -1

	if (numHijos<1 || numHijos>maxChilds)
	{
		printf("Error. Se debe introducir un numero que este entre 1 y %d \n", maxChilds);
		sintaxis();
		exit(-1):
	}



	//TODO-END-------------------------

	//TODO-BEGIN-------------------------
		//Control del número de jobs
		//Valores validos entre 1 y maxJobs
		//Si error mostramos mensaje, sintaxis y terminamos con -1
	if (numJobs<1 || numJobs>maxJobs)
	{
		printf("Error. Se debe introducir un numero que este entre 1 y %d \n", maxJobs);
		sintaxis();
		exit(-1):
	}





	//TODO-END-------------------------

	//TODO-BEGIN-------------------------
		//Declaramos el identificador del semáforo sMutex, 
		//que juega el rol de barrera del padre
		int sMutex;

	//TODO-END-------------------------

	//TODO-BEGIN-------------------------
		//Creamos e inicializamos el semáforo. 
		//Se inicializa al valor correcto para que funcione como mutex
		sMutex=sCreate(SSEED,1);
	//TODO-END-------------------------


	//TODO-BEGIN-------------------------
		//Creamos el array de estrucutras hijos llamando a NewArrayHijos
		//Esta funcion crea el array hijos, declarado globalmente en func.h
		//Si la función no devuelve el numero de hijos mostramos error y salimos con -1
		if(numHijos != NewArrayHijos(numHijos))
		{
			printf("Error al crear el array de hijos\n")
			exit(-1);
		}



	//TODO-END-------------------------


	//TODO-BEGIN-------------------------
		//Creamos los pipes de los hijos llamando a CrearPipes.
		//Esta función conoce el array hijos, pero recibe el número de ellos.
		//Si  la funcion no devuelve el numero de hijos mostramos error y salimos con -1
		if (numHijos != CrearPipes(numHijos))
		{
			printf("Error al crear los pipes\n")
			exit(-1);
		}



	//TODO-END-------------------------

	//---***Bucle para crear a los hijos***---
	//En el bucle los hijos leen los jobs de su pipe y lo procesan 
	//en exclusión mutua
	for(i=0; i < numHijos; i++) { //El padre itera creando hijos

		//TODO-BEGIN-------------------------
			//llamamos a la función fork obteneiendo en la variable pid 
			//el valor retornado

		pid=fork();
 }


		//TODO-END

		//TODO-BEGIN-------------------------
			//Si no se ha podido crear al hijo mostramos error
			//Sustituir ... por su codigo correcto
			if(pid== -1){   
				sprintf(buffer,"ERROR. Fork ha fallado al crear al hijo %d\n",i);
				perror(buffer);
				exit(-1);
			}
		//TODO-END-------------------------


		//TODO-BEGIN-------------------------
			//Sustituir ... por su codigo correcto
			//Completar los TODO que se piden
			if(pid == 0){ // Código hijo Código hijo Código hijo Código hijo Código hijo 
				//TODO-BEGIN-------------------------
					//El hijo cierra el descriptor de escritura del pipe pPC
					//porque del pipe pPC va a leer

					close(hijos[i].pPC[READ]);
					//El hijo cierra el descriptor de lectura del pipe pCP
					//porque en el pipe pCP va a escribir
					close(hijos[i].pPC[READ])


				//TODO-END-------------------------
				
				//El hijo entra en bucle a leer del pipe y procesar 
				while(doContinue){
					//TODO-BEGIN-------------------------
						//El hijo lee la carga de trabajo del pipe pPC
						//usando la función LeerPipe
						carga=LeerPipe(hijos[i].pPC[READ]);

					//TODO-END-------------------------

					//Si la carga que lee del pipe es JOB_END (0)
					//el hijo saldrá del bucle 
					if (carga==JOB_END) {
						doContinue=false;
					}
					else {
						//Se establece el caracter para este hijo
						theChar=i+65;

						//TODO-BEGIN-------------------------
							//El hijo accede mediante mutex a la funcion DoJob
							//Pasar los parametros correctos a la función DoJob
							//ver su definición en func.h
							sWait(sMutex);
							DoJob(jobsFilePath, i, carga);
							sSignal(sMutex);



						//TODO-END-------------------------

						//El hijo escribe en el pipe pCP el JOB DONE
						EscribirPipe(hijos[i].pCP[WRITE],JOB_DONE);	

					}
				}
				//El hijo cierra los descriptores de los pipes usados
				close(hijos[i].pPC[READ]);
				close(hijos[i].pCP[WRITE]);
				exit(0); //El hijo termina, no itera.
			}
			else{ //Código padre Código padre Código padre Código padre Código padre
				//TODO-BEGIN-------------------------
					//El padre cierra el descriptor de lectura del pPC
					//porque en el pipe pPC va a escribir
						close(hijos[i].pPC[READ]);


					//El padre cierra el descriptor de escritura del pCP
					//porque del pipe pCP va a leer
						close(hijos[i].pCP[WRITE]);
				//TODO-END-------------------------
				hijos[i].pid=pid;
			}
		//TODO-END-------------------------
	}

	// Aquí sólo llega el padre
	// El padre entra en bucle a enviar ordenes de trabajo a los hijos

	int jobsSent=0; 
	while(jobsSent<numJobs){
		//Selecionamos el hijo al que asignar el job
		h=RandInt(0,numHijos-1);
		//Obtenemos el pid el hijo seleccionado
		pid=hijos[h].pid;
		//Obtenemos la carga de trabajo 
		carga=RandInt(1,maxCarga);

		//TODO-BEGIN-------------------------
			//Asignamos el job al hijo enviandolo por el pipe
			//para ello llamamos a la funcion EscribirPipe. 
			//Pasar parametros correctos, ver definicion en func.h
			EscribirPipe(hijos[h].pPC[WRITE],carga);


		//TODO-END-------------------------

		//Añadimos el trabajo pendiente en la estructura del hijo
		hijos[h].jobsPending++;
		jobsSent++;
	}


	//Cuando se han enviado todos los jobs, el padre espera la contestación de
	//los hijos via su pipe. El padre recorrerá los hijos a la espera de la 
	//llegada del JOB_DONE via el pipe. Solo recorre los hijos con jobs pendientes.

	int jobsCompleted=0; 
	int pipeData;
	while (jobsCompleted<jobsSent){
		for (h=0; h<numHijos; h++){
			//Solo leemos de los pipes de hijos con jobs pendientes.
			if (hijos[h].jobsPending>0){
				//Leemos del pipe su orden JOB_DONE
				pipeData=LeerPipe(hijos[h].pCP[READ]);
				if (pipeData==JOB_DONE){
					hijos[h].jobsPending--;
					hijos[h].jobsDone++;
					jobsCompleted++;
				}
				else {
					printf("ERROR en la recepcion de JOB_DONE\n");
					exit(-1); 				
				}
			}
		}
	}

	//Cuando se ha enviado todos los jobs se envía el JOB_END a todos los hijos
	//usando el pipe pPC
	//TODO-BEGIN-------------------------
		//El padre itera por los hijos y escribiendo el JOB_EN en el pipe pPC
		for (int h = 0; h < numHijos; ++i)
		{
			pid = hijos[h].pid;
			EscribirPipe(hijos[h].pPC[WRITE], JOB_END)
			
		}



	//TODO-END-------------------------

	//TODO-BEGIN-------------------------
		//Codificar el bucle para esperar la terminación de los hijos
		//usando la funcion wait o la función waitpid
		for(i=0; i < numHijos; i++){
 			pid=waitpid(hijos[h].pid,&status,0); //Esperamos la terminación de cualquier hijo recogiendo el pid del mismo.
 		}


	//TODO-END-------------------------

	//Se guarda el conteo de jobs en el fichero jobscount.txt
	SaveJobCounts(countsFilePath, numHijos);

	//El padre cierra los descriptores de los pipes usados
	close(hijos[i].pPC[WRITE]);
	close(hijos[i].pCP[READ]);

	return 0;
}