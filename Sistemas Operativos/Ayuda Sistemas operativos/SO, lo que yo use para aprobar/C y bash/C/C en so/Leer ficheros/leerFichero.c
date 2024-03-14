#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>



int main (void)
{

	int fd=0;
	char buf[10];//Esto es un buffer para almacenar el archivo, maximo 10 bytes
	ssize_t nr_bytes;//esto es para contar los caracteres

	fd = open("/home/alu30/Escritorio/C y bash/C/C en so/Leer ficheros/ miFcihero", O_RDONLY);

	if (fd == -1 )
	{
		printf("Error al abrir el archivo \n");
	}
	else
	{
		nr_bytes = read(fd, buf, 5);
		//5 es el numero de bytes que se va a leer
		close(fd);
		if(nr_bytes == 0 )
		{
			printf("Archivo vacio");
		}
		else
		{

			printf("El numero de caracteres es: %d , contenido:  %s \n",(int)nr_bytes, buf );
		}	

		// lo de (int)nr_bytes es para pasar de ssize_t a int
	}

	return 0;
}

/*

		**Leer un fichero**

funcion open:	 int open(constant char *pathname, int flags)
funcion read:	 ssize_t read(int fd, void *buf, size_t count);
funcion close:   int close(int fd);


*/
