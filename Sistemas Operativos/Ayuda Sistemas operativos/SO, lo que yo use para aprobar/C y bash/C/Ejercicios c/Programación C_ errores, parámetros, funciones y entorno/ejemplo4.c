// =================================================================== 
// Programa #4: Consultar el valor numérico de la variable global "errno" 
// Archivo: ejemplo4.c 
// =================================================================== 
#include <stdio.h> 
#include <unistd.h> 
#include <errno.h> // La variable "errno" se declara en este fichero 
#include <string.h>
int main (int argn, char *argv[]) { 
  // Llamada al sistema para cerrar un fichero que no está abierto 
  if ( close(23) == -1) { // Lógicamente, se produce un error. ¿Cual? 
     printf ("Motivo del error de la última llamada al sistema: %d \ncuya descripcion es: %s\n", errno ,strerror(errno));
     perror("[error c004 en main]");
     return 1; 
     }
return 0; 
} 