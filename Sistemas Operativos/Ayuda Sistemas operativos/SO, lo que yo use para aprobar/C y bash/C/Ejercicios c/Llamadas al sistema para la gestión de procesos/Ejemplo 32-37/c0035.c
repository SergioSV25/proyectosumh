#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(void) {
int ret;
char *args[]={"which","ls",NULL};
char *env[]={"PATH=/etc:/tmp:/usr/bin:/bin:.","MAIL=/home/user1",NULL};
ret = execve("/usr/bin/which",args,env);
perror("exec failed");
return 0;
}