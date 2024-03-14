#! /bin/bash
userHome=~ 
	



echo "1. Mostrar fecha y hora (date)
2. Ejecutar editor ""nano""
0. Salir"
echo -e "Escriba la opcion (0-2): \c"
read var	   

case $var in
 	"1")
		 date ;;
	"2")
		 nano;;
	"0")
		exit;;	
	* )
		echo "Elige una opcion correcta";;		

esac		