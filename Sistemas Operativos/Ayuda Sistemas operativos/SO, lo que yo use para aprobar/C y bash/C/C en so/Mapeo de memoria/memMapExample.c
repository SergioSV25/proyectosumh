/*
 This program : 
 - Loads a file into virtual memory with mmap
 - Looks occurrences of one determined character in file
 - Replaces all that occurrences for another determined character in file. 
 
 Input arguments
 -  argv[1] --> file name an path
 - *argv[2] --> character to be looked for 
 - *argv[3] --> character which replaces the found ones
 
 Example: memMMapExm a A /* 'a' character will be replaced in file with 'A' character 
 */

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
  char *addr, *file_name;//valores de retorno de la funcion mmap
  int fd;//file descriptor 
  struct stat statbuf;
  char seekchar, newchar;//variables de tipo char
  
  if(argc == 4)    /* check impunt arguments are right */
  {
    file_name = argv[1];// nombre del archivo
    seekchar = *argv[2];//buscar el char para sustituirlo
    newchar = *argv[3];//caracter por el cual lo vamos a sustituir
  }
  else
  {
    printf("Error argument number \n");
    exit(1);
  }
  
  if( -1 == (fd = open(file_name, O_RDWR))) /* open file in read/write mode*/
  //primero el nombre del fichero y luego el modo de apretura 
  // y el modo de apertura es lectura y escritura
  {
    perror("Error opened file \n");
    exit(1);
  }
  
  fstat(fd, &statbuf); /* Load file status */
  //con esta funcin sabemos que tan largo es el fichero
  
  addr = mmap(NULL,statbuf.st_size, PROT_WRITE, MAP_SHARED, fd, 0); /* map file  */
  //Primer agumento es NULL y asi es kernel lo gestiona
  //segundo longitud que vamos a mapear 
  //tercero nivel de proteccion, es decir, las paginas pueden ser escritas, porque etsa el PROT_WRITE 
  //Cuarto que la visibilidad sea publica, es decir que los cambios se vuelquen el fichero
  // quinto es el fd
  //sexto queremos mapear todo desde el principio de ahi las posicion 0
  if(addr == MAP_FAILED) /* check mapping successful */
  {
    perror("Error  mapping \n");
    exit(1);
  }
  
    printf("\nfile contents before:\n%s \n", addr); /* write current file contents */
  
  for(size_t i = 0; i < statbuf.st_size; i++) /* replace characters  */
  {
    if (addr[i] == seekchar)
    {
       (addr[i] = newchar) ;
    }
  }
     
  printf("\nfile contents after:\n%s \n", addr); /* write file contents after modification */
     
  return 0;
}