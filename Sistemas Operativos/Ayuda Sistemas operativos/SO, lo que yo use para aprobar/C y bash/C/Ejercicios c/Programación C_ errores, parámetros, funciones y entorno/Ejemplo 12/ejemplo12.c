// =========================================================
// Programa #12: Separación de las rutas de la variable PATH
// Archivo: ejemplo12.
// =========================================================
#include <stdio.h>
#include <string.h>
#include <unistd.h>
extern char **environ; // Declaración externa de environ
// Prototipos de las funciones utilizadas
// Consultar la variable de ambiente PATH: Devuelve la variable en si
static char *GetEnvPath(void);
// Consultar la variable de ambiente PATH: Devuelve el índice de la variable en el array de entorno
static int GetEnvPath2 (void);
// Extraer las distintas rutas desde la variable de ambiente PATH
static int GetPathDirs(char *path,char *patharray[],int arraysize);
// Mostrar las rutas ya separadas
static void PrintPaths(char *paths[],int arraysize);
//----------------------------------------
int main (void){
char *pathexp; 
char pathbuf[1000]; 
char *paths[100]; 
int count;
//Una forma de obtener el PATH
pathexp = GetEnvPath();
//Otra forma de obtener el PATH
pathexp = environ[GetEnvPath2()];
strcpy (pathbuf,pathexp);
count = GetPathDirs(pathbuf,paths,100);
PrintPaths (paths,count);
return 0;
}
//----------------------------------------
static char *GetEnvPath (void) {
int i;
for ( i=0; environ[i]!=NULL; i++) {
    if (memcmp(environ[i],"PATH=",strlen("PATH=")) == 0) {
        return environ[i];
        }
    }
return "";
}
static int GetEnvPath2 (void) {
int i;
for ( i=0; environ[i]!=NULL; i++) {
    if (memcmp(environ[i],"PATH=",strlen("PATH=")) == 0) {
        return i;
        }
    }
return -1;
}
//----------------------------------------
static int GetPathDirs (char *path, char *array[], int size){
int i; 
int pos;
path+=strlen("PATH="); 
array[0]=path;
for ( i=0,pos=1; path[i]!=0; i++) {
    if ( path[i]==':' ) {
        path[i]=0;
        array[pos++] = path+i+1;
        if (pos == size) 
            return size;
        }
    }    
return pos;
}
//----------------------------------------
static void PrintPaths (char *paths[], int size) {
int i;
printf ("Total de rutas encontradas: %d\n", size);
for (i=0; i<size; i++)
    printf ("%d. : %s\n", i+1, paths[i] );
} 
  