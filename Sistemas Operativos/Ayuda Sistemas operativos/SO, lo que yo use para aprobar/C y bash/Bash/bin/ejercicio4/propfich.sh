#! /bin/bash

userHome=~ 

if [[ -f $1 ]]
then 
	echo "Fichero encontrado: "
	echo "Directorio donde se ubica el archivo: " 
	pwd 
	echo "Permisos de los archivos: "
	ls -l
elif [[ $# -ne 1 ]]; 
then
		echo "Se debe de introducir un archivo"	
else
	echo "El fichero no existe" 

fi	
	
#Notas ejercicio: simplemenmte comprobamos si ha introducido un parametro
# si es asi todo bien, si son menos o mas da error
#Luego una vez comprobado que el fichero existe pasa por los comandos pwd 
# y ls -l.



