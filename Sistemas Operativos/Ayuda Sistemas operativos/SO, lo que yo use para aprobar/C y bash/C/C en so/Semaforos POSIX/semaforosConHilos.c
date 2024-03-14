#include<pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define NR_LOOP 10000
//Explicacion avanzada en el txt o mas abajo

static int counter = 0;
sem_t sem1;

static void * thread_1_function(void* arg);
static void * thread_2_function(void* arg);

int main(void)
{
	
	sem_init(&sem1, 0, 1);
	pthread_t thread_1, thread_2;
	pthread_create(&thread_1, NULL, *thread_1_function, NULL);
	pthread_create(&thread_2, NULL, *thread_2_function, NULL);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	printf(" valor counter = %d \n", counter);
	return 0;
}

static void * thread_1_function(void* arg)
{

	for (int i = 0; i < NR_LOOP; ++i)
	{
		sem_wait(&sem1);
		counter +=1;
		sem_post(&sem1);
	}
}

static void * thread_2_function(void* arg)
{

	for (int i = 0; i < NR_LOOP; ++i)
	{
		sem_wait(&sem1);
		counter -=1;
		sem_post(&sem1);
	}
}


/*		**Semáforos

¿Qué es?
		 - Mecanismo de sincronización
		 - Protegen acceso a una "sección crítica"

Funciones

		int sem_init (sem_t *sem, int pshared, unsigned in value);
	//Primera argumento es el semaforo, el segundo es si es compartivo entre procesoso
	// el tercero es el valro de inicializacion 
		int	sem_wait (sem_t *sem);
		int sem_post (sem_t *sem);

		sem_init inicializa el semaforo 
		sem_wait decrementa en una unidad el semaforo o para bloquear el acceso 
		sem_post incrementra en una unidad el semaforo o para desbloquear el acceso
*/	


				 							