#incluye <stdio.h>
#incluye <stdlib.h>
void main (){
  if ( fork() == 0 ) 
      printf ("Este es el hijo\n");
  else
      printf ("Este es el padre\n");
exit(EXIT_SUCCESS);
}