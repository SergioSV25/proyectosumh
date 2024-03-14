#! /bin/bash

#Al poner esto significa que lo siguienet que le pases por consola cuando ejecutes el archivo se guaradra
#Es decir llamas al archivo a ejecucion y luego le pasas el parametro
#Asi: alu30@so:~/Escritorio$ CaseStatement.sh Mercedes
#Esa variable se gauradara en el car=$1

echo -e "Enter a character: \c"
read value


case $value in
 	[a-z])
		echo "User entered $value between a to z" ;;
	[A-Z])
		echo "User entered $value between A to Z";;
	[0-9])
		echo "User entered $value between 0 to 9";;
	? )
		echo "User entered $value special character";;	
	* )
		echo "Unknown input";;		

esac		