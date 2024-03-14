#! /bin/bash
userHome=~ 


fechin=$(date) 
echo ""
echo "Fecha / hora inicio: $fechin"; 

while ((1)); 
do
	echo "Fecha / hora actual: $(date) "; 
	sleep 60 #segundos
	echo "Fecha / hora inicio: $fechin"; 
	(( count++ ))
done
exit 0
#Simplemente un contador, poco mas
#Para ejecutarlo en segundo plano se pone Tick60.sh &
#Para matarlo kill -p <su pid>