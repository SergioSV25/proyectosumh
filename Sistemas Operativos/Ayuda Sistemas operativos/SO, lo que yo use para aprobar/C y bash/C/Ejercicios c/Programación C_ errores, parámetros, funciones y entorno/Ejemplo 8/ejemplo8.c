// ===================================================================
// Programa #8: Uso de las constantes 
// Archivo: ejemplo8.c
// ===================================================================
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