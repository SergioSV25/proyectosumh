#include <sys/mman.h>//
#include <sys/stat.h>//      
#include <fcntl.h>//Estos tres son del shm_open
#include<unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#define SMOBJ_NAME "/myMemoryObj"
#define SMOBJ_SIZE 200
//Explicacion avanzada en el txt o mas abajo
//PARA HACER QUE FUNCIONE HAYQ QUE ESCRIBIR -LRT EN LA CONSOLA:
//gcc sm_create.c -o sm_create -lrt

int main(void)
{
	int fd;
	fd = shm_open(SMOBJ_NAME, O_CREAT | O_RDWR, 00600);
	//Lo primero es el nombre del objeto de memoria
	//el segundo argumento es un flag que indica que hacemos
	//los flags estan en sh_open man, que en este caso es 
	//leer y escribir
	//el tercer argumento son los permisos de los usuarios
	//para que solo nosotros tengamos acceso ponemos ese numero
	if(fd == -1)
	{
		printf("error\n");
		exit(1);
	}
	if (-1 == ftruncate(fd, SMOBJ_SIZE))
	 {
	 	printf("error\n");
		exit(1);
	 } 
	 close(fd);
	return 0;
}

/*		** POSIX Shared Memory**
			( Mecanismo IPC)

- Se "comparte" una region de memoria
- Se llama "sahared memory objects"
- En linux --> /dev/shm
- System Shutdown --> se borran
- Sincronización!!	
	

Funciones:
	int shm_open(const char *name, int oflag, mode_t mode);
	void *mmap(.., MAP_SHARED....);
	ftruncate(int fd, off_t length);
	int fstat(...);
	*/