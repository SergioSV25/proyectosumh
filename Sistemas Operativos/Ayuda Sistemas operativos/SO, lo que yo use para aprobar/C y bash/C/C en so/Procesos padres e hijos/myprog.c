#include<stdio.h>


int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; ++i)
	{
		printf("argumento %d, %s \n", i, argv[i] );
	}

	printf("argc = %d \n", argc);
	printf("argv[argc] = %s \n", argv);
	return 0;
}


//En el argv[0] simpre tendra el nombre con el que se invoca al programa


/*
	** Argumentos en la línes de comandos **
	 (Command line arguments "argc, *argv[]")

-Argumentos que se le pasan al programa al ser ejecutado
	./myprog arg1....argN	 

- Argumentos de entrada en "main"
	-argc -> "argument count"
	-argv -> "argument vector"
	
	int main(int argc, char *argv[])

 */