#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>   
#include <signal.h>   
#include <stdlib.h>
#include <string.h>
#define NUMHIJOS 5 
//Definimos una unión usada en sigqueue
union sigval value;
 
//fijamos el número de hijos 
const int numHijos = NUMHIJOS; 
int pids[NUMHIJOS]; //guarda los pid's de los hijos de los que se recibe señal
//variable contador de señales recibidas
int senyalesRecibidas;
//*****************************************************************
//FUNCIÓN que envía la señal al padre
//*****************************************************************
void EnviarSenyal(){
 value.sival_int = getpid(); //Asignamos el valor al dato
 //Enviamos una señal al padre con el pid del hijo para que me envíe el ACK
 sigqueue(getppid(), SIGRTMIN, value);  //Usamos sigqueue para enviar señales en tiempo real
}
//*****************************************************************
//FUNCIÓN que envía el ACK al hijo
//*****************************************************************
void EnviarAck(int pid){
 //Enviamos el ACK al hijo.
 kill(pid,SIGUSR1); //usamos kill para enviar señales normales
 printf("Enviado ACK a hijo %d\n",pid);
}
//***************************************************
//MANEJADORA que gestiona las señales recibidas en padre e  hijos
//***************************************************
void Handler(int signo, siginfo_t *info, void *context){
 if (signo==SIGUSR1){ //Señal recibida por el hijo
 printf ("Hijo %d recibe ACK del padre usando la señal %d.\n",getpid(),signo);
 }
 else if (signo==SIGRTMIN){ //Señal recibida por el padre
 pids[senyalesRecibidas]=info->si_pid;
 senyalesRecibidas++; // incrementamos el contador de señales recibidas
 printf ("Recibida señal %d (#%d) del hijo %d.\n",signo,senyalesRecibidas,info->si_pid);
 }
}
//FUNCION que muestra el array de pid's recibidos (simplemente con ánimo de debug)
void MostrarPids(){
 int i;
 for(i=0; i<numHijos-1; i++)
 printf("%d:",pids[i]);
 printf("%d\n",pids[numHijos-1]);
}
 
int main( int args, char *argv[] )
{
 int i;       
 int pid;    
 senyalesRecibidas=0;
 struct sigaction action;
 int status;
 char buffer[100];
 
 //Inicializamos el array de pids que envían
 for(i=0; i<numHijos; i++) pids[i]=0;
 
 //Tenemos un manejador (Handler) que atenderá a las distintas señales, el manejador se instala antes del fork
 
 //Instanciamos en el manejador la señal que usará el padre en la estrucutra Action y registramos el manejador de esa señal
 action.sa_sigaction = Handler;
 action.sa_flags = SA_SIGINFO;
 sigaction(SIGRTMIN, &action, NULL); //Usaremos una señal de tiempo real
 //Instanciamos en el mismo manejador la señal que usará el hijo en la estrucutra Action y registramos el manejador de esa señal
 action.sa_sigaction = Handler;
 action.sa_flags = SA_SIGINFO;
 sigaction(SIGUSR1, &action, NULL); //Usaremos una señal normal
 
 //---***Bucle para crear a los hijos***---
 //En el bucle los hijos envían su señal, reciben su ACK y terminan.
 for(i=0; i < numHijos; i++) { //El padre itera creando hijos
 pid=fork();
 if(pid == -1){   
    sprintf(buffer,"ERROR. Fork ha fallado al crear al hijo %d\n",i);
    perror(buffer);
    exit(-1);
 }
 if(pid == 0){
 //Código hijo
    printf("Hijo %d envía señal.\n", getpid());
    EnviarSenyal();
    printf("Hijo %d esperando ACK\n", getpid());
    pause();
    printf("El hijo %d termina.\n",getpid());
    exit(0); //El hijo termina, no itera.
 }
 }
    //Aquí sólo llega el padre
 //Bucle para esperar las señales de los hijos
 while(senyalesRecibidas < numHijos){
 pause(); //Bloquea al padre hasta que llegue una señal que debe ser tratada en el manejador, o morirá.
     MostrarPids();
 }
 
 printf("El padre envía ACKs\n");
 sleep(1); 
 //Enviamos los ACKS
 for (i=0; i<numHijos; i++)
 EnviarAck(pids[i]);
 
 printf("El padre entra a esperar la terminación de los hijos\n");
 //Bucle para esperar la terminación de los hijos y notificarlo
 for(i=0; i < numHijos; i++){
 pid=waitpid(-1,&status,0); //Esperamos la terminación de cualquier hijo recogiendo el pid del mismo.
 printf("El hijo con pid %d ha terminado\n",pid);
 }
 return 0;
}