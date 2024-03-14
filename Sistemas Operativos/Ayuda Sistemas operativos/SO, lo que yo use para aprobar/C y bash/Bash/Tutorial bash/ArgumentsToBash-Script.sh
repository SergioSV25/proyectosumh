#! /bin/bash

echo $0 $1 $2 $3 '> echo $1 $2 $3'

#Guarda el argumento com un array
args=("$@")

#Para imprimir lo que haya en esa posicion
echo ${args[0]} ${args[1]} ${args[2]} ${args[3]} ${args[4]} ${args[5]}

#para imprimir todo el array
echo $@

#Para imprimir el numero de argumentos que le hemos pasado
echo $#