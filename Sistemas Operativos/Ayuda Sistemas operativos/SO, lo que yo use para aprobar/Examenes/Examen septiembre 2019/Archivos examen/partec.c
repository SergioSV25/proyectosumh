#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
//#include "sem.h"
#include "functions.h"

typedef struct { 
    int pid ; // Pid del hijo 
	int pipehijo[2]; // Descriptores el pipe del hijo
	int ceros; //ceros contados por el hijo
	int pares; //pares no nulos contados por el hijo
	int impares; //impares no nulos contados por el hijo
} HIJO;

int main( int argc, char **argv ){
	int i,j,r,c,pid,key,wstatus,dim,rows,cols,numChilds,matrixSize;
	int blockSize;
	int ceros=0,pares=0,impares=0;

	int numBlocks;
	int condHijosMod16, condDivHijos;
	char filename[50];
	 
	char buffer[100];
	int shmId, shmSize;
	int *shmMatrix; //unrolled matrix in shared memory

	
	//Inicializamos el generador de números aleatorios
	srand(getpid());   // Initialization, should only be called once.

	//Obtenemos los parámetros de la linea de comandos
	numChilds=atoi(argv[1]);
	dim=atoi(argv[2]);

	// La matriz es cuadrada por lo que el numero de filas y columnas es el indidcado en el parametro dim
	rows=dim;
	cols=dim;  


	//Realizamos al comprobación de parametros con la función CheckParameters
	//Si los parametros no son correctos llamamamos a PrintCorrectChilds para mostrar al usuarios el 
	//numero correcto de hijos que se pueden usar para esa matrix de dim x dim
	if ( !CheckParameters(numChilds,rows) ) {
		printf("Tamaño de bloque no homogéneo o matrix demasiado grande.\n");
		//Mostramos los numeros de hijos que se pueden usar para una matriz de tamaño dim x dim
		PrintCorrectChilds(rows);
		exit(1);
	}

	//Tamaño de bloque
	blockSize = (int) BlockSize(rows,cols,numChilds);

	//BEGIN TODO *************************************************************
	// Reservar de Memoria compartida para una matriz de enteros de rows x cols
	// Vincularse al segmento obtenido
	// Gestionar los errores.

	shmSize = dim * sizeof(int);
	shmId = shmget(ftok(".", SHMSEED), shmSize, IPC_CREAT | SHMPERMISOS);







	//END TODO *************************************************************

    //LLamamos a la funcíon InitMatrix para inicializar el segmento de memoria compartida de la matriz.
 	//printf("El padre inicializa el array de memoria compartida con id: %d\n",shmId);
    InitMatrix(shmMatrix, rows, cols);

	//BEGIN FOR DEBUG ------------------------------------------------------
		//Mostramos la Matriz en pantalla (tener en cuenta que si es muy grande no se ve bien, probar con 10x10)
			//PrintMatrix(shmMatrix,rows,cols);

		// Mostramos el contenido de los datos (bloques de la matriz) para cada hijo
		// Los hijos comienzan por 0. Una matriz con 4 bloques (uno para cada hijo) serían los hijos 0,1,2,3
			//for (i=0;i<numChilds;i++){
			//	PrintBlockData(i, shmMatrix, rows, cols, numChilds);
			//}
	//END FOR DEBUG ------------------------------------------------------

	//BEGIN TODO *************************************************************
	// El padre crea un array de estructuras HIJO 
	



	//END TODO *************************************************************
	 
	//BEGIN TODO *************************************************************
	//Inicializamos el array de estructuras HIJO, con valores por defecto todo a cero excepto el campo pipe
	//para el que creamos un pipe para cada hijo 






	//END TODO *************************************************************


	//BEGIN TODO *************************************************************
    //Bucle para crear a los hijos
    //Controlar los errores
    //Se crean los hijos sin esperar a que terminen para crear el siguiente.
    //El código del hijo:
    	//Cierra el lado del pipe que no use
		//Crea un array de enteros donde obtendrá su parte de la matriz de memoria compartida
		//Obtiene su parte de matriz compartida con la función GetBlock llamandola asi:
    	//   GetBlock(shmMatrix,i,rows,cols,numChilds,rows,&block[0]); donde block es un array que declara 
        //                                                             para recibir los datos del bloque.
		//LLama a las funciones ContarCeros, ContarParesNoCeros,ContarImpares y ContarDecena para obtener sus datos
		//Una vez obtenidos los envía (write) al padre mediante el pipe.
		//El hijo termina
    //El código del padre (dentro del bucle for de creación de los hijos)
    	//El padre actualiza el pid del hijo recien creado en su estructura dentro del array de HIJOS.
		//El padre cierra el lado del pipe que no usa.

	for(i=0; i < numChilds; i++)	{ 
	    //El padre crea un hijo


		//El padre comprueba que no ha fallado fork





		if(      ){
		//Código hijo
			//El hijo cierra el lado de lectura de su pipe


			//El hijo define un array de enteeros block de tamaño blockSize
			//y obtiene el bloque que le corresponde de shmMatrix utilizando la funcion GetBlock


		 	//El hijo obtiene los datos que le piden (ceros, pares, impares, decena1, decena2 ... )
		 	//utilizando las funciones contadoras




		   //El hijo envía sus datos al padre mediante su pipe




		   //El hijo termina. No itera por el bucle.
		   exit(0); 
		}
		else{
			//El padre actualiza el pid del hijo en su estructura


			//El padre ciera el lado de escritura del pipe del hijo

		}
	}
	//END TODO *************************************************************


 	// Aquí sólo llega el padre    

	//BEGIN TODO *************************************************************
    //Bucle de espera a la terminación de los hijos
 		//El padre espera la terminación de un hijo
 		//Cuando el hijo termina lee sus datos del pipe y los actualiza en su estructura HIJO
	 	int ixChild; 
		for(i=0; i < numChilds; i++){
			//Esperamos la terminación de cualquier hijo recogiendo el pid del mismo.

			//Buscamos cual es el pipe del hijo



			//El padre lee del pipe del hijo que ha terminado y actualiza los datos globales



		}
	//END TODO *************************************************************


	//BEGIN TODO *************************************************************
	//Han terminado todos los hijos el padre agrega los datos de cada HIJO sumandolos en las variables
	//ceros, pares e impares que están definidas al comienzo del código.





	//END TODO *************************************************************

	//Si han terminado todos los hijos el padre genera el informe de resultados con la funcion SaveData 
	//(que hay que completar en functions.c) 
	SaveData(ceros,pares,impares);

	//BEGIN TODO *************************************************************
	// El padre se desvincula del segmento de memoria compartida (controlar posibles errores)



	//END TODO *************************************************************


	//BEGIN TODO *************************************************************
    //El padre borra el segmento de memoria compartida.


	//END TODO *************************************************************

    //El padre termina
	return 0;
} 
