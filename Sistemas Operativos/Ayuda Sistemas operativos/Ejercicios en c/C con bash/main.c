// ==========================
// Programa #1: Hola Mundo !!
// Archivo: holamundo.c
// ==========================

/*
#include <stdio.h>

int main(void) {
printf("Hola mundo\n");
return 0;
}
*/
//   Lo compilaríamos con:
//   $ gcc holamundo.c -o holamundo


// =======================================================
// Programa #2: Paso de parámetros desde la línea de órdenes
// Archivo: ejemplo2.c
// =======================================================
/*
#include <stdio.h>

int main (int argn,char *argv[])
{
int i;
printf("Número de argumentos: %d\n",argn);
printf("Nombre del programa : %s\n",argv[0]);
// Mostramos el resto de parámetros
for(i=1;i<argn;++i) {
        printf("Hola");
   printf("Argumento %d = %s\n",i,argv[i] );
   }
return 0;
}
*/

// ===================================================================
// Programa #4: Consultar el valor numérico de la variable global "errno"
// Archivo: ejemplo4.c
// ===================================================================
/*
#include <stdio.h>
#include <unistd.h>
#include <errno.h> // La variable "errno" se declara en este fichero
#include <string.h>
int main (int argn, char *argv[]) {
  // Llamada al sistema para cerrar un fichero que no está abierto
  if ( close(23) == -1) { // Lógicamente, se produce un error. ¿Cual?
     printf ("Motivo del error de la ultima llamada al sistema: %d \ncuya descripcion es: %s\n", errno ,strerror(errno));
     perror("[error c004 en main]");
     return 1;
     }
return 0;
}
*/

// ===================================================================
// Programa #8: Uso de las constantes
// Archivo: ejemplo8.c
// ===================================================================
/*
#include <stdio.h>
#include <unistd.h>
#include <errno.h> // La variable "errno" se declara en este fichero
#include <string.h>
int main (int argn, char *argv[]) {
  // Llamada al sistema para cerrar un fichero que no está abierto
  if ( close(-23) == -1){ // Lógicamente, se produce un error. ¿Cual?
      if (errno==EBADF) {
          // Bad file descriptor
          printf ( "Descriptor de fichero incorrecto\n" );
          }
      else if (errno==EIO) {
              // Input/Output Error
              printf ( "Error físico de E/S\n" );
              }
      else {
         printf ( "Error: %s\n", strerror(errno) );
         }
   }
return 0;
}
*/


// ===========================================
// Programa #9: Tabla de variables de ambiente
// Archivo: ejemplo9.c
// ===========================================
/*
#include <stdio.h>
int main (int argn, char *argv[], char *env[]) {
  int i;
  for (i=0; env[i]!=NULL; i++) {
       printf ("%s\n",env[i]);
       }
return 0;
}
*/
/*
// ===========================================
// Programa #10: Tabla de variables de ambiente
// Archivo: ejemplo10.
// ===========================================
#include <stdio.h>
#include <unistd.h>

extern char **environ; // Declaración externa de environ
int main (void) {
  int i;
  for (i=0; environ[i]!=NULL; i++)
      printf ("%s\n",environ[i]);
return 0;
}
*/
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    fork(); // En este punto el programa crea un clon de si mismo

    printf("Hola mundo, mi identificador de proceso es: %d\n", getpid());
}
