#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main (){
unsigned int status;
if ( fork() == 0 ){ /* ==0 en el hijo */
  scanf("%d",&status);
  exit (status);
  }
else { /* !=0 en el padre */
  wait (&status);
  printf ("hijo exit status = %d\n",status >> 8);
  }
exit (0);
}