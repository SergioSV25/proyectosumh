#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
 
static void manejadoraA (int sig){
    printf("Recibida señal %d\n",sig);
}
static void manejadoraB (int sig, siginfo_t *siginfo, void *context)
{
    // Atención: Evitar el uso de printf en la función manejadora pues no se garantiza su 
    // correcto funcionamiento dentro de ellas. Usar write en su lugar. En este caso 
    // funciona porque es lo único que hace la función manejadora. En la man page de 
    // signal(2) hay una relación de funciones y llamadas que pueden ser llamadas desde la 
    // función manejadora sin problemas, printf no es una de ellas. 
 
    printf ("Recibida señal %d y de PID: %ld, UID: %ld\n", sig, (long)siginfo->si_pid, (long)siginfo->si_uid);
}
 
int main (int argc, char *argv[])
{
    struct sigaction act;
    printf("Mi PID = %d\n",getpid());
 
    memset (&act, '\0', sizeof(act)); //Garantizamos que la estructura está a cero. Se puede obviar, el compilador la inicializará.
    //OPCION A
        // Use the sa_handler field if  the handles does not have two additional parameters 
        act.sa_handler = &manejadoraA;
    //--------------
    //OPCION B
        // Use the sa_sigaction field because the handles has two additional parameters. 
        // The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler.
           //act.sa_sigaction = &manejadoraB;
           //act.sa_flags = SA_SIGINFO;
    //--------------
 
    if (sigaction(SIGINT, &act, NULL) < 0) {
        perror ("Error en sigaction al establecer la función manejadora.");
        return 1;
    }
 
    while (1)
        sleep (10);
 
    return 0;
 }  

 /* En este ejemplo tenemos dos opciones para instalar el manejador. 
 	La opción A, que es la que está sin comentar utiliza la función manejadoraA 
 	que simplemente muestra un texto con la señal que llega. Si queremos obtener 
 	más información como por ejemplo el PID y el UID del proceso que envía debemos usar la opción B. 
 	Entonces la función manejadora recibirá una estructura siginfo_t con la información adicional, 
 	que es la que muestra en su printf.

	En el ejemplo utilizamos un bucle sin fin donde ponemos a dormir al proceso durante 10 segundos
	 y la señal que se captura es SIGINT. Como hemos dicho sigaction reestablece el manejador 
	 automáticamente. La señal SIGINT es la que se envía cuando se pulsa CTRL-C para matar al proceso. 
	 Como la capturamos y por tanto no morimos, sino que sacamos un printf por pantalla, 
	 entonces para poder matar este ejemplo debemos usar el PID que nos muestra para enviar una señal 
	 SIGKILL desde otro terminal a dicho proceso.
*/	 
