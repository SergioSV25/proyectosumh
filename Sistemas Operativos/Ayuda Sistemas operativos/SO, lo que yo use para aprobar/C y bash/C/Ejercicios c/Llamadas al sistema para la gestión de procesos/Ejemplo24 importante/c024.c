/*  Este programa muestra algunas técnicas típicas de programación de procesos.

  El programa principal crea dos procesos hijos para ejecutar el mismo bucle de impresión 
  y mostrar un mensaje antes de salir. Para el proceso padre (p.e. el programa principal), 
  después de crear dos procesos hijos entra en un proceso de espera ejecutando la llamada al sistema wait(). 
  En el momento en que alguno de los dos procesos hijos termina, 
  el padre comienza la ejecución y el PID del proceso que ha terminado se retorna al padre, el cual se puede imprimir.

  Puesto que hay dos procesos hijos, habrán dos wait()s, uno para cada proceso hijo.

  En este ejemplo no utilizamos el valor de “estado” retornado.

  En este ejemplo, veremos que el padre no tiene porqué esperar inmediatamente después 
  de crear los dos hijos, pero sí tiene que esperar su terminación antes de acabar el.



  El programa principal crea dos procesos hijos. 
  Ambos procesos llaman a ProcesoHijo(). El proceso padre llama a la función ProcesoHijo(). 
  Esta función calcula todos los números de Armstrong desde el 0 hasta el 9999. 
  Un número de Armstrong es un entero cuyo valor es igual que la suma de sus dígitos elevado a 4. 
  Después de esto el proceso padre entra en un estado de espera, hasta que termine alguno de sus hijos. 
  Puesto que los dos hijos se ejecutan concurrentemente, 
  no tenemos forma de predecir cual de ellos terminará primero
 */



// ===========================================
// Programa: Ejemplo de fork
// Archivo : fork5.c o c024.c
// ===========================================
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define MAX_COUNT 200
#define BUF_SIZE 100
#define QUAD(x) (x*x*x*x)
// Prototipos de los procesos padre e hijo
void ProcesoHijo (char *, char *);
void ProcesoPadre (void);
int main (void) {
pid_t pid1, pid2, pid;
int status;
int i;
char buf[BUF_SIZE];
printf("*** El proceso padre realiza el fork() - 1 ***\n");
pid1 = fork();
if (pid1 < 0) {
   printf("Fallo al crear proceso 1\n");
   exit(1);
   }
if (pid1 == 0) {
   ProcesoHijo("Primero", " ");
   }
printf("*** El proceso padre realiza el fork() - 2 ***\n");
pid2 = fork();
if (pid2 < 0) {
   printf("Fallo al crear proceso 2\n");
   exit(1);
   }
if (pid2 == 0) {
   ProcesoHijo("Segundo", " ");
   }
// El proceso padre se pone a trabajar
ProcesoPadre();
sprintf(buf, "*** El padre entra en estado de espera .....\n");
write(1, buf, strlen(buf));
pid = wait(&status);
sprintf(buf, "*** El padre ha detectado que el proceso hijo %d ha terminado ***\n", pid);
write(1, buf, strlen(buf));
pid = wait(&status);
printf("*** El padre ha detectado que el proceso hijo %d ha terminado ***\n", pid);
printf("*** El proceso padre termina ***\n");
exit(0);
}
void ProcesoPadre (void) {
int a, b, c, d;
int abcd, a4b4c4d4;
int count = 0;
char buf[BUF_SIZE];
sprintf(buf, "El padre calcula números de Armstrong\n");
write(1, buf, strlen(buf));
for (a = 0; a <= 9; a++)
 for (b = 0; b <= 9; b++)
   for (c = 0; c <= 9; c++)
    for (d = 0; d <= 9; d++) {
      abcd = a*1000 + b*100 + c*10 + d;
      a4b4c4d4 = QUAD(a) + QUAD(b) + QUAD(c) + QUAD(d);
      if (abcd == a4b4c4d4) {
       sprintf(buf, "Desde el padre: El %d-esimo número de Armstrong es %d\n", ++count, abcd);
       write(1, buf, strlen(buf));
       }
    }
sprintf(buf, "Desde el padre: hay %d números de Armstrong\n", count);
write(1, buf, strlen(buf));
}
void ProcesoHijo(char *number, char *space) {
pid_t pid;
int i;
char buf[BUF_SIZE];
pid = getpid();
sprintf(buf, "%sEl proceso hijo %s comienza (pid = %d)\n",space, number, pid);
write(1, buf, strlen(buf));
for (i=1; i<=MAX_COUNT; i++) {
  sprintf(buf, "%sSalida del proceso hijo %s, Valor=%d\n", space, number, i);
  write(1, buf, strlen(buf));
  }
sprintf(buf, "%sEl proceso hijo %s (pid = %d) va a terminar\n", space, number, pid);
write(1, buf, strlen(buf));
exit(0);
}