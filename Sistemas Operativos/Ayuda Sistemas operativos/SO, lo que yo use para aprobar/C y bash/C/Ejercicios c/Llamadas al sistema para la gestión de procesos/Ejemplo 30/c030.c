#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void ChildFun(int *ptr) {
  *ptr=100;
  exit (0); // stdlib.h
}
int main(void) {
  int ret; 
  int p=10;
  if ((ret=fork()) == -1) {
     perror("fork failed");
     return 1;
     }
  
  if (ret==0) {
     ChildFun(&p);
     }
  // Codigo del padre
  wait (&ret); // Espera la finalización del hijo
  printf ("p=%d\n", p);
  
  return 0;
}

/* El hijo hereda las variables del padre, pero cuando las modifica, 
    modifica su copia de dichas variables, no las del padre, 
    por eso el padre cuando muestra el valor de la variable p, 
    lo está haciendo de su variable p que no ha sido modificada por el hijo. 
    Éste modificó su variable p, pero no la mostró.
*/    