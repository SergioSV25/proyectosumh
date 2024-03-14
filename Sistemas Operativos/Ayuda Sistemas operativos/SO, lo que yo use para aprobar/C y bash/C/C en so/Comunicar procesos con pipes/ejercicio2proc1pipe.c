/****************************************************************/
/* Programar "ls -l | wc > file1.txt"                            */
/* El archivo file1.txt existe                                  */
/* TODO: manejo de errores                                      */
/****************************************************************/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>


#define READ_END    0    /* index pipe extremo lectura */
#define WRITE_END   1    /* index pipe extremo escritura */

#define FILE_NAME  "file.txt"   /* nombre del archivo donde escribir */

int main(int argc, char* argv[])   
{
    int fd1[2],fd2;
    int status, pid;
    
    pipe(fd1);                  /* comunica ls y wc */
    
    pid = fork();     

    if(pid == 0)                /* hijo 1, ejecuta "ls -la" */
    {              
        close(fd1[READ_END]);   
        /* cerrar extremo no necesario 
			El hijo 1 va a escribir en el estremo de 
			escritura del pipe.
			Para rllo hay que cerrar el extremo de lectura y que no se quede abierto.
        */
        
        dup2(fd1[WRITE_END], STDOUT_FILENO); 
        //El dup es para que nos escriba en el extremo de escritura del pipe
        //asi escribira en el otro extremo
        close(fd1[WRITE_END]);
        
        execlp("/bin/ls", "ls", "-la", NULL);
        /*
			 Las funciones execlp y execvp duplicarán las acciones  
			 del  shell  al  buscar  un  fichero
       		 ejecutable si el nombre de fichero especificado 
       		 no contiene un carácter de barra inclinada(/). 
       		 El camino de búsqueda es el especificado en el entorno 
       		 por la variable PATH. 

        */
    }
    else                          /* padre */
    { 
        close(fd1[WRITE_END]);    /* extremo no necesario ya y lo cierra el padre */
        
        pid = fork();
		
       if(pid == 0)               /* hijo 2, ejecuta "wc" */
       {     
          fd2 = open(FILE_NAME, O_WRONLY);
          //abrimos el archivo
          dup2(fd1[READ_END], STDIN_FILENO);
          //de aqui leemos lo que nos ha pasado el hijo 1, de ahi que sea read
          close(fd1[READ_END]);
		   		   
          dup2(fd2, STDOUT_FILENO);		   
            
          execlp("/usr/bin/wc","wc",NULL);
       }
       else /* padre */
       {
           close(fd1[READ_END]);      /* cerrar extremo no necesario */    
       }                
     }
    
   /* wait para cada hijo */
    wait(&status);   
    wait(&status);    
    
    return 0;    
}
    

/*		

-------------------------------------------------------
		Programar. "ls -l | wc > file.txt"
-------------------------------------------------------		

1.- ls -l: listar informacion de archivos
2.- wc:	   muestra número de líneas, palabras y bytes
3.- >:     redirecciona la salida STDOUT a... (file.txt)	


Se utilizarán:		fork(), dup2(...),
					execlp(...), pipe(...)

*/