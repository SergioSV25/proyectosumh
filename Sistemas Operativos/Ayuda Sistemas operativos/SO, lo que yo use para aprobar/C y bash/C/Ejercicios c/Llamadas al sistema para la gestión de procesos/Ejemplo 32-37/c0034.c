#include <stdio.h>
#include <unistd.h>
int main(void) {
int ret;
char *args[] = {"ls","-l","a*",NULL};
printf("ls Is About to start....\n");
ret=execve("/bin/ls",args,NULL);
perror("exec failed");
return 0;
}