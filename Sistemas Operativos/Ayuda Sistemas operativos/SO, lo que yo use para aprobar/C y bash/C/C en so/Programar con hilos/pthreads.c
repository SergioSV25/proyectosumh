#include <pthread.h>
#include <stdlib.h>
#include <sys/stat.h>
#include<unistd.h>
#include <stdio.h>
#include <fcntl.h>
//Explicacion avanzada en el txt o mas abajo

void *thread_routine(void *arg)// esta es la rutina que estamos definiendo
{
	int nr_lines= *((int*)arg);//Para poder pasarle un entero hay que convertirlo
	int fd;
	char buf[] = "Nueva linea \n";
	printf("El hilo comienza a ejecutarse...\n");
	for (int i = 0; i < nr_lines; ++i)
	{
		fd = open("/home/alu30/Escritorio/C y bash/C/C en so/Programar con hilos/file.txt", O_WRONLY|O_APPEND);
		write (fd, buf, sizeof(buf)-1);
		close(fd);
		//Aqui abrimos el archivo, escribimos y lo cerramos
	}
}
int main(int argc, char *argv[])
{
	pthread_t thread1;
	int value;
	if(argc >1)
	{
	  value = atoi(argv[1]);
	}
	else
	{
		printf("Tienes que pasar un argumento \n");
	}

	if (0 != pthread_create(&thread1, NULL, thread_routine, &value))
		return -1;
	//al crear el hilo tenemos que pasarle el puntero al hilo creado, los atributos del hilo,
	//la rutina que va a ejecutar el hilo, y los argumentos de entrada de la rutina

	pthread_join(thread1, NULL);

	return 0;
}

/*		** Hilos: threads **

Funciones utilizadas:
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
int pthread_join(pthread_t thread, void **retval);

Ejemplo:
	CRear un hilo que escribe x lineas en un archivo de texto

*/