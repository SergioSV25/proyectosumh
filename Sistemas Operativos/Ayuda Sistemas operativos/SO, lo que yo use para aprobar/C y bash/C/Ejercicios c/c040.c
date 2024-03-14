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
}