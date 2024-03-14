
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void FillWithz(char *ptr, unsigned int nr_bytes);
int main(int argc, char const *argv[])
{
	char *ptr = NULL;
	unsigned int nr_bytes;

	scanf("%u", &nr_bytes);
	ptr = malloc(nr_bytes);
	if (ptr != NULL)
	{
		FillWithz(ptr, nr_bytes);
		free(ptr);
	}

	return 0;
}


static void FillWithz(char *ptr, unsigned int nr_bytes)
{
	for (int i = 0; i < nr_bytes; ++i)
	{
		*ptr = 'z';
		ptr++;
	}

}


/*
		**Asignación  Dinámica de memoria**
		    (dynamic memory allocation)

- ¿Qué es?	-> asignación en tiempo de ejecución
			-> reserva em uma region de memoria
			   llamada "heap"

- Funciones:
		void *malloc(size_t size);
		void free(void *ptr);			     

*/		