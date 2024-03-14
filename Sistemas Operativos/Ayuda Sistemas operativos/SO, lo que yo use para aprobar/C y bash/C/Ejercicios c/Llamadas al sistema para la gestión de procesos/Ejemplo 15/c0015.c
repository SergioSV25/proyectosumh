#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
void main (void){
pid_t childpid;
int status;
if ((childpid = fork()) == -1) {
   perror ("Fork ha fallado");
   exit(1);
   } 
else if (childpid == 0)
        fprintf(stderr, "Soy el hijo con pid = %ld\n", (long)getpid());
else if (wait(&status) != childpid)
        fprintf (stderr, "Wait interrumpido por una señal\n");
else fprintf (stderr, "Soy el padre con pid = %ld\n",(long)getpid());
exit(0);
}