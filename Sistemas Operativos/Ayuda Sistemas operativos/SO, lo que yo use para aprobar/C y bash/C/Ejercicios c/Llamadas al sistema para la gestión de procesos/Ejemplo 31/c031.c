#include <stdio.h>
#include <unistd.h>
int main(void) {
int ret,pid,status;
if ((ret=fork())==-1) { 
   perror(0); 
   return 1; 
   }
if (ret==0) { 
   printf("Child Living..."); 
   exit(10); 
   }
pid=wait(&status);
if (pid==-1) { 
   printf("No Child\n"); 
   exit(0); 
   }
printf ("Child PID(%d) Terminated\n",pid);
if ((status & 0xFF)==0) { // Got a legal status
   printf("Child Returned (%d)\n",status>>8);
   exit(0);
   }
if ((status & 0xFF00)==0) { // Process Terminated Signal !!
   printf("Signal terminated child - Signal %d\n",status & 0x7F);
   if((status & 0x0080)>0) { 
      printf("Child Performed CORE Dump\n"); 
      }
   exit(0);
   }
if ( (status & 0xFF) == 0x7F) {
   printf("Signal Stopped Child for Debugging \n");
   printf("Signal Id (%d)",status>>8);
   exit(0);
   }
printf("**** This Line Should Never be executed ****");
return 0;
}

/* Vemos las distintas posibilidades de capturar el valor de terminación del hijo 
   y determinar cómo ha terminado su ejecución.
*/