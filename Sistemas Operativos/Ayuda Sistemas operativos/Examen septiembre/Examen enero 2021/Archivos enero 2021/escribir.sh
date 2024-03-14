#!/bin/bash

ERR_NOT_NUMBER=1
ERR_OUT_OF_RANGE=2

MIN_HIJOS=1
MAX_HIJOS=26
MIN_JOBS=1
MAX_JOBS=100


Number(){
	#----------------------------------
	# NO TOCAR - PODEIS USARLA EN CheckArguments() para determinar si un parámetro  es numérico
	# Parámetros: eimo-
	#    $1 : parametro a comprobar
	# Salida:
	#    1  : si es numérico
	#    0  : si no es numérico
	#----------------------------------
	if [ "$1" -eq "$1" ] 2>/dev/null; then
		return 0
	else
		return 1
	fi
}


ord() {
	#----------------------------------
	# NO TOCAR
	#----------------------------------
	# Devuelve el indice de la tabla ascii para el caracter recibido como paramtro
	# Ejemplo:
	# ord A  --> imprime 65
	  LC_CTYPE=C printf '%d' "'$1"
}

chr() {
	#----------------------------------
	# NO TOCAR
	#----------------------------------
	# Devuelve el caracer ascii del índice recibido como paramtro
	# Ejemplo:
	# chr 65  --> imprime A
	printf "\x$(printf "%x" "$1")"
}



Sintaxis(){
	#----------------------------------
	# NO TOCAR
	#----------------------------------
	#Debe de mostrar la sintaxis de uso del programa, con la explicación de los parametros.
	echo "-------------------------------------------------------------------------------------------"
	echo "escribir.sh <numHijos> <numPiezas>"
	echo ""
	echo "Los parametros son obligatorios:"
	echo "numHijos     : Es el número de hijos que se van a lanzar"
	echo "               El valor mínimo para este parámetro es $MIN_HIJOS"
	echo "               El valor máximo para este parámetro es $MAX_HIJOS"
	echo "maxPiezas    : Es el número de jobs que se van a lanzar"
	echo "               El valor mínimo para este parámetro es $MIN_JOBS"
	echo "               El valor máximo para este parámetro es $MAX_JOBS"
	echo "-------------------------------------------------------------------------------------------"
}

StrLen(){
	#----------------------------------
	# NO TOCAR
	#----------------------------------
	#Devuelve la longitud de la cadena que se pasa por parametro
	str=$1
	echo ${#str}
}


ToNumber(){
	#----------------------------------
	# NO TOCAR
	#----------------------------------
	#Convierte una cadena de caracteres a numero.
	#No hace compobaciones todos los caracteres deben ser numeros. Se adminte el . decimal
	str=$1
	echo $(bc -l <<<"${str}")
}

ShowResults(){
	#----------------------------------
	# NO TOCAR
	#----------------------------------
	#Se muestran los resultados.
	printf "Se han lanzado %d jobs para %d hijos\n" $NUM_JOBS $NUM_HIJOS
	for (( i=0; i<${#letras[@]}; i++ ))
	do
		letraindex=$(( $i+65 ))
		letra=`chr $letraindex`
		echo "$letra($letraindex) #${letras[$i]} en ${jobs[$i]} jobs"
	done
}


#***************************************************************************
# Completar las siguientes funciones según el enunciado y los comentarios.
#***************************************************************************

CheckArguments(){
#----------------------------------
# BEGIN TODO
#----------------------------------
	#Comprobamos que el número de parametros es 2

	#Comprobamos que el parámetro numHijos es un número

	#Comprobamos el rango del parámetro numHijos

	#Comprobamos que el parámetro numJobs es un número

	#Comprobamos el rango del parámetro numJobs

#----------------------------------
# END TODO
#----------------------------------
}


InitData(){
	#----------------------------------
	# BEGIN TODO
	#----------------------------------
	#Necesitamos inicializar los arrays letras y jobs a ceros.
	#Inicializar ambos array con todos sus componentes a cero.
	#El número de componentes a inicializar es el maximo posible (MAX_HIJOS)




	#----------------------------------
	# END TODO
	#----------------------------------
}

LoadResults(){
	#----------------------------------
	# BEGIN TODO
	#----------------------------------
	#Se lee el fichero jobsfile.txt caracter a caracter hasta final de fichero
	#Cada vez que leo un caracter obtengo su valor de orden en la tabla ascii
	#El índice del array letras donde tengo que operar para ese caracter
	#lo obtenemos restando 65 al número de orden obtenido
	#Se incrementa en uno el valor del array letras en el índice calculado






	#----------------------------------
	# END TODO
	#----------------------------------

	#----------------------------------
	# BEGIN TODO
	#----------------------------------
	#Se lee el fichero jobscount.txt linea a linea hasta final de fichero
	#Cada linea es el valor de jobs que ha ejecutado el hijo cuyo indice 
	#en el array de jobs es el orden de la línea leida (empezando por cero)
	#Asignar a ese ínidce del array jobs el valor leido.






	#----------------------------------
	# END TODO
	#----------------------------------

}

#----------------------------------------------
# MAIN
#----------------------------------------------

#----------------------------------
# BEGIN TODO
#----------------------------------
	#Comprobar los argumentos llamando a CheckArguments apropiadamente

#----------------------------------
# END TODO
#----------------------------------


#----------------------------------
# BEGIN TODO
#----------------------------------
	#Borramos los ficheros jobsfile.txt y jobscount.txt de una posible 
	#ejecución anterior sin mostrar error en caso de no existir.


#----------------------------------
# END TODO
#----------------------------------


#Una vez comprobado que todo correcto asignamos los parametros a variables
NUM_HIJOS=$1
NUM_JOBS=$2

#----------------------------------
# BEGIN TODO
#----------------------------------
	#Llamamos al ejecutable procesar (o procesar_profesor) pasándole 
	#el numero de hijos y el numero de jobs totales a repartir entre los hijos.

#----------------------------------
# END TODO
#----------------------------------

#Declaramos los arrays para contar los caracteres escritos por cada hijo
#y el numero de jobs 
declare -a letras
declare -a jobs
	
#LLamamos a la inicialización de los arrays. 
InitData 

#----------------------------------
# BEGIN TODO
#----------------------------------
	#LLamamos a la función LoadResults que cargará los arrays con los datos
	#de los ficheros.

#----------------------------------
# END TODO
#----------------------------------

#----------------------------------
# BEGIN TODO
#----------------------------------
	#LLamamos a la función ShowResults que mostrará los resultados

#----------------------------------
# END TODO
#----------------------------------

#----------------------------------
# FIN
#----------------------------------