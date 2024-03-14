#include <stdio.h>
#include <unistd.h>
int main(void) {
int ret;
if ((ret=fork())==-1) { 
   perror("Fork Failed"); 
   return 1; 
   }
if (ret==0) { // child
   char *args[]={"/bin/dir","-l","c008.c",NULL};
   execve("/bin/ls",args,NULL);
   perror("Exec Failed"); 
   return 1;
   }
wait(&ret); // wait for child
printf("Estado de salida del hijo: %d, %d\n", WEXITSTATUS(ret), ret >> 8); 
return 0;
}