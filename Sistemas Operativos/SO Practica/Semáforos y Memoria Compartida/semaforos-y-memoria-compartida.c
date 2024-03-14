#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>   
#include <signal.h>   
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>   
#include <sys/shm.h>  
#include "./sem.h"

#define NUMHIJOS 5 
#define SSEED 99
#define SHMSEED 35 
#define SHMPERMISOS 0644

const int numHijos = NUMHIJOS; // fijamos el número de hijos 
 
int main (int args, char *argv[])
{
    int i, j;       
    int pid;    
    struct sigaction action;
    int status;
    char buffer[100];
    int shmId, shmSize;
    int *shmArray; // Puntero del proceso donde ubicaremos el segmento de memoria compartida.
    int sBarreraPadre; // Declaramos el identificador del semáforo que juega el rol de barrera del padre

    sBarreraPadre = sCreate(SSEED, 0); // Creamos el semáforo inicializado a cero
    
    int sACKS[NUMHIJOS]; // Declararmos el array de semáforos para los ACKs de los hijos y los inicializamos a cero
   
    for(i = 0; i < numHijos; i++) 
    {
        sACKS[i] = sCreate(SSEED+i+1, 0);
    }

    shmSize = 6 * sizeof(int); // Segmento de memoria compartida, un array de 6 enteros.
    printf("Tamaño del segemento a pedir: %d\n", shmSize);

    shmId = shmget(ftok("/bin/ls", SHMSEED), shmSize, IPC_CREAT | SHMPERMISOS); // Creamos el segmento y asignamos correctamente los punteros.
    shmArray = shmat(shmId, 0, 0);

    printf("El padre inicializa el array de memoria compartida con id: %d\n",shmId);
    memset(shmArray, 0, shmSize);

    // BUCLE PARA CREAR A LOS HIJOS --> envían su señal, reciben su ACK y terminan.
    for(i = 0; i < numHijos; i++) // El padre itera creando hijos
    { 
        pid = fork();

        if(pid == -1)
        {   
            sprintf(buffer, "ERROR. Fork ha fallado al crear al hijo %d\n", i);
            perror(buffer);
            exit(-1);
        }

        if(pid == 0) // Código hijo
        {
            printf("Hijo %d llega a su barrera.\n", getpid()); // El hijo indica que ha llegado a la barrera
            sSignal(sBarreraPadre);

            printf("Hijo %d esperando ACK\n", getpid()); // El hijo espera en su semaforo de ACK para seguir.
            sWait(sACKS[i]);

            printf("Hijo %d lee Array Compartido con id %d\n", getpid(), shmId); //El hijo lee la memoria compartida

            for (j = 0; j < 6; j++)
            {
                printf("%d ",shmArray[j]);
                printf("\n");
            }
            
            printf("El hijo %d se desvincula del array\n", getpid()); // El hijo se desvincula del array.
            shmdt(shmArray);

            printf("El hijo %d termina.\n", getpid());
            exit(0); // El hijo termina, no itera.
        }
    }


    // Aquí sólo llega el padre

    // El padre espera a que todos los hijos lleguen a la barrera
    for (i = 0; i < numHijos; i++)
    {
        sWait(sBarreraPadre);
        printf("Un hijo ha llegado a su barrera\n");
    }

    printf("Todos los hijos han pasado su barrera\n");

    // El padre escribe en la memoria compartida, vemos el valor inicial y el nuevo.
    printf("El padre escribe el array de memoria compartida con id: %d\n",shmId);
    for (i = 0; i < 6; i++)
    {
        printf("%d->", shmArray[i]); 
        shmArray[i] = i;
        
        printf("%d ", shmArray[i]); 
    }
    printf("\n");

    printf("El padre envía ACKs\n"); // Enviamos los ACKS
    
    for (i = 0; i < numHijos; i++)
    {
        sSignal(sACKS[i]);
    }

    printf("El padre entra a esperar la terminación de los hijos\n");

    // Bucle para esperar la terminación de los hijos y notificarlo
    for(i = 0; i < numHijos; i++)
    {
        pid = waitpid(-1, &status, 0); // Esperamos la terminación de cualquier hijo recogiendo el pid del mismo.
        printf("El hijo con pid %d ha terminado\n",pid);
    }

    // El padre se desvincula del array.
    printf("El padre se desvincula del array\n");
    shmdt(shmArray);

    // El padre borra el array
    printf("El padre se destruye del array\n");
    shmctl(shmId, IPC_RMID, 0);

    printf("El padre termina\n");

    return 0;
}