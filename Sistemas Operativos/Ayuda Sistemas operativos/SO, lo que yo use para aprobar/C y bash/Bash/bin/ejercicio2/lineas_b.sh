#! /bin/bash


if [[ $# -ne 1 ]]
then
	echo "Error lineas_b: Número incorrecto de parámetros
	Sintaxis: lineas_b <file_name>
	donde:
	file_name: es el nombre del fichero de entrada"
	
elif [[ ! -f $1 ]]
then
	echo "Error lineas_b: El fichero no existe
	Sintaxis: lineas_b <file_name>
	donde:
	file_name: es el nombre del fichero de entrada"
else	

	tail -n 8 $1 | head -n 4 > $1.lineas		
fi
#El tail coge 8 lineas de abajo arriba y el head
#coge de la primera a las 4 siguientes y para que coja de la 5 a la 8
#utilizamos un pipe ( | ) que hace el tail y el resultado se lo pasa luego al head.
#POnemos despues del 8 un $1 porque le estamos pasando que pille las 
#lineas entre la 5 y la 8 del archivo almacenado en $1.
#Por ultimo guradamos eso en un archivo con > $1.lineas
#que es coger todo y se gurada en un archivo con el nombre del archivo que esta
#almacenado en $1 concatenado con .lineas (como nos pide)