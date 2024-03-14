#! /bin/bash

#Forma1
#El read lo que hace es leer lo que le pases por consola lo guarda
#en esa variable 
while read p
do
	echo $p
done < ReadFile.sh
#El done < ReadFile.sh lo que hace es redirigir el while al archivo
#Es decri, una vez finalizado al while volvera a coger el archvio
#Especificado

#Forma 2
#Aqui vamos a usar un cat con un pipe, que lo que haces 
#Es que cada cosa que lea el cat de lo dara como input al while
#mediante el pipe
cat ReadFile.sh | while read p
do
	echo $p
done

########################################################################
########################################################################
#La forma 1 y la forma 2 leen el fichero tal cual, a diferencia        #
#de la forma 3 que lee el fichero que le pases solo y no todo el codigo#
########################################################################
########################################################################

#Forma 3
#Entre el ifs y el read debe de haber un espacio ya que no le estamos asignando al ifs el read
#Estamos asignandole un espacio.
#Tambein introducimos el -r para que el backslash no se interprete 
while IFS= read -r line
do
	echo $line
done < test