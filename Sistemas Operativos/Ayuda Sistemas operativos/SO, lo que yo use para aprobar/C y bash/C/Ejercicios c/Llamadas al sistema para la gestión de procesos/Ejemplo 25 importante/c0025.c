#include <stdio.h>
#include <stdlib.h>
int main() {
unsigned int status;
if (fork()==0) { /* ==0 en el hijo */
   // Pedimos por teclado
   printf("Proceso Hijo: Introduce el estado de terminación : ");
   scanf("%d",&status);
   // El proceso hijo termina
   exit(status);
   } 
else { /* !=0 en el padre */
   // El padre se queda esperando a que el proceso hijo termine
   wait(&status);
   // Cuando el hijo acaba, imprimimos el valor de estado retornado por éste
   printf("Estado de salida del hijo: %d, %d\n", WEXITSTATUS(status),  status >> 8);
   }
}