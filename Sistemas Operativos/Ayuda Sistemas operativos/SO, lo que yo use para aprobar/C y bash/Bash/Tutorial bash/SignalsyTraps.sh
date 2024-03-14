#! /bin/bash



file=/home/alu30/Escritorio/file.txt

trap "rm -f $file && echo file deleted; exit" 0 2 15
#Los numeros son el tipo de señal trap, 
#eso se puede ver con el comando man 7 signal
#y si bajamos nos encontraremos una tabla 


#trap "echo Exit signal is detected" SIGKILL SIGSTOP
#SIGHILL o SIGSTOP no funciona con trap

#Con $$ se escribe el pid
echo "pid is $$"
while (( COUNT < 10 ))
do
	sleep 10
	(( COUNT ++ ))
	echo $COUNT
done
exit 0	


#Para empezara debugear el codigo en un punto en concreto
# se debe escribir set -x y todo lo que haya debajo entrara en modo debug
#si queremos pararlo en algun punto en concreto ponemos set +x
#es decir seria:
#	codigo
#	set -x
#-----codigo----
#-----codigo----
#	set +x
#	codigo
#	codigo


#Kill -9 <pid> para matarlo
