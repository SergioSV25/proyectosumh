#! /bin/bash

#El -e sirve para que se pueda interpretar el \c (sino se imprimira tal cual)
#El \c sirve para que el cursor se quede en la misma linea tras imprmir
echo -e "Enter the name of the file or directory: \c"
read fileName

#Dentro de la condicion del if el -e sirve para poder ver si ese archivo existe o no
#Forma 1
if [[ -e $fileName ]]
then
	echo "$fileName found"
else
	echo "File not found"	
fi	

#Forma 2 para comprobar si el fichero existe, no vale cualquier archivo, tiene que ser (file)
if [[ -f $fileName ]]
then
	echo "$fileName found"
else
	echo "File not found"	
fi	

#Forma 3 para comprobar si el directorio existe
if [[ -d $fileName ]]
then
	echo "$fileName found"
else
	echo "Directory not found"	
fi

#Forma 4 para comprobar si el fichero esta no vacio
if [[ -s $fileName ]]
then
	echo "File not empty"
else
	echo "$fileName is empty"	
fi	