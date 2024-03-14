#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
extern char **environ;
int main(void) {
  char *args[]={"which","ls",NULL};
  execve("/usr/bin/which",args,environ);
  perror("exec failed"); return 0;
}