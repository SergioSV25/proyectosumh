#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
extern char **environ; 
int main(void) {
int ret;
if ((ret=fork())==-1) { 
   perror("Fork Failed"); 
   return 1; 
   }
if (ret==0) { // child
   char *args[]={"/bin/sh", "-c", "ls -l *.c",NULL};
   execve("/bin/sh",args,environ);
   perror("Exec Failed"); 
   return 1;
   }
wait(&ret); // wait for child
printf("Estado de salida del hijo: %d, %d\n", WEXITSTATUS(ret), ret >> 8); 
return 0;
}