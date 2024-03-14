#include <stdio.h>
#include <unistd.h>
int main(void) {
int ret;
char *args[] = {"ls","-l","/usr/bin",NULL}; // Long Listing
printf("ls Is About to start....\n");
ret=execve("/bin/ls",args,NULL);
perror("exec failed");
return 0;
}