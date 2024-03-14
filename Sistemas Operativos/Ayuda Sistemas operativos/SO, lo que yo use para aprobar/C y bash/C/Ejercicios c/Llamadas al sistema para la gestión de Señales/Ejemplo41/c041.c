#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> // alarm()
#include <string.h>
#include <signal.h> // sigaction(), sigsuspend(), sig*()
//#include <sys/siginfo.h>
//Declaracion de funciones
void handle_signal(int signal);  //Función manejadora de señales
void handle_sigalrm(int signal); //Función manejadora de las alarmas
void do_sleep(int seconds);      //Función para enviar a dormir al proceso
int ContHUP;
int ContUSR1;
int ContRTMIN;
const int SLEEP_TIME=10;
//Esta función nos permitirá ver la máscara de señales.
void print_sigset_t(sigset_t *set)
{
 int i;
 i = SIGRTMAX;
 do {
 int x = 0;
 i -= 4;
 if (sigismember(set, i+1)) x |= 1;
 if (sigismember(set, i+2)) x |= 2;
 if (sigismember(set, i+3)) x |= 4;
 if (sigismember(set, i+4)) x |= 8;
 printf("%x", x);
 } while (i >= 4); 
 printf("\n");
}
/* Compilarlo y ejecutarlo
 * 
 * Mostrará el PID, que puede ser usado desde otro terminal para enviarle señales
 *     $ kill -HUP <pid>
 *     $ kill -USR1 <pid>
 *     $ kill -ALRM <pid>
 *
 * Termina el programa con CTRL-C ( = SIGINT) o enviando SIGKILL, SIGTERM
 */
int main() {
    //Primero vemos un ejemplo de cómo se ve un conjunto de señales en un sigset_t 
 sigset_t set;
 sigemptyset(&set);
        print_sigset_t(&set);
     /* add signals to set */
     sigaddset(&set, SIGINT);  printf("+ SIGNINT\n"); print_sigset_t(&set);
     sigaddset(&set, SIGHUP);  printf("+ SIGHUP\n");  print_sigset_t(&set);
     sigaddset(&set, SIGALRM); printf("+ SIGALRM\n"); print_sigset_t(&set);
 sigemptyset(&set);
    print_sigset_t(&set);
   
    ContHUP=0;
    ContUSR1=0;
    ContRTMIN=0;
     // Declaramos la esttructura sigaction
    struct sigaction sa;
    print_sigset_t(&sa.sa_mask);
    // Mostramos el pid para poder enviar señales desde otro shell
    printf("Mi pid es: %d\n", getpid());
    // Establecemos el manegador de las señales.
    sa.sa_handler = &handle_signal;
    // Indicamos el flag de restart, que reinicia el setup de la señal si es posible
    sa.sa_flags = SA_RESTART;
    // Bloquea cualquier señal durante el manejador
    sigfillset(&sa.sa_mask);
    // Intercepts SIGHUP, SIGURSR1 and SIGINT
    if (sigaction(SIGRTMIN, &sa, NULL) == -1) {
        perror("Error: NO se pudo establecer el manejador para SIGRTMIN"); // No debería ocurrir
    }
    else{
        printf("SIGHUP - Manejador establecido\n");
    }
    if (sigaction(SIGHUP, &sa, NULL) == -1) {
        perror("Error: NO se pudo establecer el manejador para SIGHUP"); // No debería ocurrir
    }
    else{
        printf("SIGHUP - Manejador establecido\n");
    }
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error: No se puedo establecer el manejador para SIGUSR1"); // No debería ocurrir
    }
    else{
        printf("SIGUSR1 - Manejador establecido\n");
    }
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error: No se pudo establecer el manejador para SIGINT"); // No debería ocurrir
    }
    else{
        printf("SIGINT - Manejador establecido\n");
    }
    // Intentamos manejar SIGKILL que es la señal que forzará la muerte del proceso
    if (sigaction(SIGKILL, &sa, NULL) == -1) {
        perror("No se pudo establecer el manejador para SIGKILL"); // Siempre ocurrirá
        printf("Nunca se te permitirá manejar SIGKILL ...\n");
    }
    //Entramos en bucle a dormir
    for (;;) {
        printf("\n(Main) Durmiendo durante ~%d seconds\n",SLEEP_TIME);
        do_sleep(SLEEP_TIME); // Later to be replaced with a SIGALRM
        printf("\n(Main) Me he despertado.\n");
    }
}
//Definición del manejador de las señales excepto SIGARLM (que tiene el suyo propio)
void handle_signal(int signal) {
    const char *signal_name;
    char buffer[200];
    sigset_t pending; //Definimos un sigset para las que tenemos pendientes.
    // Deteriminamos que señal estamos manejando
    switch (signal) {
        case SIGHUP:
            ContHUP++;
            signal_name = "SIGHUP";
            sprintf(buffer,"    Capturada SIGHUP (#%d) (signal %d - %s)\n", ContHUP, signal,signal_name);
            write(STDERR_FILENO, buffer,  strlen(buffer));
            break;
        case 34:
            ContRTMIN++;
            signal_name = "SIGRTMIN";
            sprintf(buffer,"    Capturada SIGRTMIN (#%d) (signal %d - %s)\n", ContRTMIN, signal,signal_name);
            write(STDERR_FILENO, buffer,  strlen(buffer));
            break;
        case SIGUSR1:
            ContUSR1++;
            signal_name = "SIGUSR1";
            sprintf(buffer,"    Capturada SIGUSR1 (#%d) (signal %d)\n", ContUSR1,  signal);
            write(STDERR_FILENO, buffer,  strlen(buffer));
            break;
        case SIGINT:
            sprintf(buffer,"    Capturada SIGINT, saliendo ahora (signal %d)\n", signal);
            write(STDERR_FILENO, buffer,  strlen(buffer));
            exit(0);
        default:
            sprintf(buffer,"    Capturada señal desconocida: %d\n", signal);
            write(STDERR_FILENO, buffer, strlen(buffer));
            //fprintf(stderr, "Caught wrong signal: %d\n", signal);
            return;
    }
    sprintf(buffer, "    Capturada %s, a dormir durante ~%d seconds\n    Intenta enviar otra señal SIGHUP / SIGINT / SIGALRM (o más) entre tanto\n", signal_name,SLEEP_TIME);
    write(STDOUT_FILENO, buffer,  strlen(buffer));
    /*
        Todas las señales están bloqueadas durante este manejador
        Cuando durante el manejador llegan nuevas señales, sólo se marca 
        como pendiente la primera de cada tipo de señal, el resto del mismo 
        tipo se pierde, no se encolan.
        Si enviamos al proceso HUP, INT, HUP en ese orden, se trata el primer HUP,
        se encola INT y se encola HUP. Al terminar el procesado del primer HUP,
        se lanza el procesado del siguiente HUP y finalmente el INT que causa la terminación.
        El segundo HUP es procesado antes del INT porque es del mismo tipo de que la señal
        que se estaba tratando en el manejador.
        Si enviamos al proceso HUP, USR1, INT en ese orden, se trata el primer HUP
        se detecta pendiente el USR1 pero se trata INT, que termina el proceso. 
        Para que no se pierdan las distintas señales del mismo tipo que llegan
        mientras estamos en el manejador tendremos que utilizar señales en tiempo real
        que son las señales SIGRTMIN (34) y siguientes, hasta SIGRTMAX.
        Mientras que sólo puede haber encolada una de las señales normales para cada tipo,
        para las de tiempo real se encolan todas las del mimso tipo. 
    */
    do_sleep(SLEEP_TIME);
    sprintf(buffer, "    (Manejador) Me despierto despues de %d segundos\n", SLEEP_TIME);
    write(STDOUT_FILENO,  buffer, strlen(buffer));
    // Bien, que es lo que me has enviado mientras dormía?
    sigpending(&pending); //Capturamos el conjunto de señales pendientes
    if (sigismember(&pending, SIGHUP)) { //Miramos si una SIGHUP está pendiente
        sprintf(buffer,"    Al menos una SIGHUP está pendiente\n");
        write(STDERR_FILENO, buffer, strlen(buffer));
    }
    if (sigismember(&pending, SIGUSR1)) { //Miramos si una SIGUSR1 está pendiente
        sprintf(buffer,"    Al menos una SIGUSR1 está pendiente\n");
        write(STDERR_FILENO, buffer, strlen(buffer));
    }
    if (sigismember(&pending, SIGRTMIN)) { //Miramos si una SIGUSR1 está pendiente
        sprintf(buffer,"    Al menos una SIGRTMIN está pendiente\n");
        write(STDERR_FILENO, buffer, strlen(buffer));
    }
    sprintf(buffer, "    (Manejador) Termino de manejar la señal %s\n\n", signal_name);
    write(STDERR_FILENO, buffer, strlen(buffer));
}
//Definición del manejador de SIGALRM
void handle_sigalrm(int signal) {
    char buffer[100];
    if (signal != SIGALRM) {
        sprintf(buffer, "    Capturada señal erronea %d\n", signal);
        write(STDERR_FILENO, buffer, strlen(buffer));
    }
    sprintf(buffer,"    Capturada SIGALRM, do_sleep() termina.\n");
    write(STDERR_FILENO, buffer, strlen(buffer));
}
void do_sleep(int seconds) {
    struct sigaction sa;
    sigset_t mask;
    char buffer[100];
    
    sa.sa_handler = &handle_sigalrm; // Intercept and ignore SIGALRM
    //Quitamos el handler tras la primera señal. Esto lo hace por defecto signal() pero sigaction() no. 
    sa.sa_flags = SA_RESETHAND; // En este caso nos interesa, pues así en el manejador no se atiende una segunda SIGALRM
    sigfillset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);
    
    // Obtenemos el conunto (mascara) de señales actual (las que se bloquean)
    sigprocmask(0, NULL, &mask);
    // Quitamos del conjunto (de la mascara) de señales a bloquear la SIGALRM para que llegue.
    sigdelset(&mask, SIGALRM);
    //sigdelset(&mask, SIGINT); //Con esta linea comentada, SIGINT estará bloqueada durante el manejador 
    // Establecemos una alarma de los segundos indicados. Vencidos los mismos recibieremos una señal SIGALRM.
    // (Infor adicional: Las alarmas no se heredan con fork)
    alarm(seconds);
    // Esperamos los segundos indicados especificando la máscara de bloqueos (que ya no tiene a SIGALRM)
    // Suspendemos el proceso con la máscara especificada
    sigsuspend(&mask);
    sprintf(buffer, "Termina sigsuspend()\n");
    write(STDERR_FILENO, buffer, strlen(buffer));
}