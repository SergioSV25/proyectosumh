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