// =========================================== 
// Programa #9: Tabla de variables de ambiente 
// Archivo: ejemplo9.c 
// =========================================== 
#include <stdio.h> 
int main (int argn, char *argv[], char *env[]) { 
  int i; 
  for (i=0; env[i]!=NULL; i++) {
       printf ("%s\n",env[i]); 
       }
return 0; 
} 