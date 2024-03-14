#include <stdio.h>
#include <unistd.h>
int main(void) {
  printf("I'm the parent with PID=%d\n",getpid() );
  if (fork()==0) {
     printf ("\nMy parent is PPID=%d\n",getppid() );
     return 0;
     }
  return 0;
}