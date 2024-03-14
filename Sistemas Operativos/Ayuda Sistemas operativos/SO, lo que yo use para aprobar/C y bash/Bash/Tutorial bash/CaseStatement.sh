
#! /bin/bash

#Al poner esto significa que lo siguienet que le pases por consola cuando ejecutes el archivo se guaradra
#Es decir llamas al archivo a ejecucion y luego le pasas el parametro
#Asi: alu30@so:~/Escritorio$ CaseStatement.sh Mercedes
#Esa variable se gauradara en el car=$1
car=$1

case $car in
 	"Audi")
		echo "Rent of $car is 100 euros" ;;
	"Volvo")
		echo "Rent of $car is 50 euros";;
	"Mercedes")
		echo "Rent of $car is 130 euros";;
	"Nissan")
		echo "Rent of $car is 90 euros";;	
	* )
		echo "Unknown car";;		

esac		