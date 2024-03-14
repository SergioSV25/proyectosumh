// ====================================================== 
// Programa #11: Consulta de la variable de ambiente PATH 
// Archivo: ejemplo11.c 
// ====================================================== 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
extern char **environ; // Declaración externa de environ 
int main (void) { 
  int i; 
  for (i=0; environ[i]!=NULL; i++) {
      if (memcmp(environ[i],"PATH=",5) == 0) {
          printf ("La variable PATH vale: %s\n",environ[i]+5); 
          break; 
          }
      }
return 0; 
}