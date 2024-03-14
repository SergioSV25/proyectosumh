#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
void main(int argc, char *argv[]) {
pid_t childpid;
int status;
if ((childpid = fork() == -1)) {
   perror("Fork ha fallado");
   exit(1);
   } 
else if (childpid == 0) { /*codigo del hijo*/
        if (execvp(argv[1], &argv[1]) < 0) {
            perror("exec ha fallado");
            exit(1);
            }
     } 
else /*codigo del padre*/
   while (childpid != wait(&status))
          if ((childpid == -1) && (errno != EINTR))
             break;
exit(0); 
}
