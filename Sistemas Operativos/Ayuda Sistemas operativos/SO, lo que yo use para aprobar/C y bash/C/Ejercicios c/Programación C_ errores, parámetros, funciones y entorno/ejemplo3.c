// ===========================================
// Programa #3: Llamada al sistema con error
// Archivo: ejemplo3.
// ===========================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argn, char *argv[]) {
if ( fork() == -1 ) {
   printf ("La llamada a fork ha fallado ...\n");
   exit (1); // o return 1;
   } 
else {
   printf ("La llamada a fork se ha realizado con exito...\n");
   exit(0); // o return 0; 
   }  
}