#include <sys/mman.h>//
#include <sys/stat.h>//      
#include <fcntl.h>//Estos tres son del shm_open
#include<unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMOBJ_NAME "/myMemoryObj"

//Explicacion avanzada en el txt o mas abajo


int main(void)
{
	int fd;
	char buf[] = "Hola soy el proceso que escribe \n";
	char *ptr;
	fd = shm_open(SMOBJ_NAME, O_RDWR, 0);
	//Lo primero es el nombre del objeto de memoria
	//el segundo argumento es un flag que indica que hacemos
	//los flags estan en sh_open man, que en este caso es escribir
	//el tercer argumento son los permisos de los usuarios
	//que en este caso es solo 0 porque anteriormente pusimos que solo
	//podiamos acceder nosotros
	if(fd == -1)
	{
		printf("error\n");
		exit(1);
	}
	 ptr = mmap(0, sizeof(buf), PROT_WRITE, MAP_SHARED, fd, 0); 
	 //El primer argumento sera 0 paraque lo haga el kernel
	 //En el sgundo le pasamos el size del buf
	 //En el tercero el flag que encontratemos en mmap man 
	 //El cuarto arguemento siempre es MAP_SHARED
	 //El quinto es el fd
	 //El sexto es desde donde vamos a empezar a escribir
	 if (ptr == MAP_FAILED)
	 {
	 	printf("error\n");
		exit(1);
	 }
	 memcpy(ptr, buf, sizeof(buf));
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
	 void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
	ftruncate(int fd, off_t length);
	int fstat(...);
	*/