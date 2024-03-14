// ===================================================================
// Programa #13: Obtención del valor de una variable de ambiente con getenv()
// Archivo: ejemplo13.c
// ===================================================================
#include <stdio.h>
#include <stdlib.h>
int main (int argn, char *argv[]) {
int i;
char *valor;
// Si sólo tenemos un argumento (nombre del programa) salimos.
if (argn < 2) exit(1);
// Mostramos el valor de todas las variables especificadas (si existen)
for ( i=1; i<argn; i++) {
    valor = getenv ( argv[i] );
    if ( valor == NULL ) {
        printf ("Variable de ambiente '%s' no definida\n", argv[i]);
        } 
    else {
        printf ("V13 alor de '%s' = %s\n",argv[i], valor);
        }
    }
return 0;
}