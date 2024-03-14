#! /bin/bash

userHome=~ 


while (( count <= 60 )); 
do
	echo "Fecha: $(date +%D)"
	echo "Hora:  $(date +%T)"
	sleep 1
	(( count++ ))
done
exit 0
#Simplemente un contador, poco mas