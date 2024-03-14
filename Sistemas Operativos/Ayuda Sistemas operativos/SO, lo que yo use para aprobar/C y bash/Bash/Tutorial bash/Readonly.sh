#! /bin/bash


var=31

readonly var
#Cuando declaramos el comando readonly (variable)
#La variable que le pasemos sera solo de lectura
#Es decir no se podra reescribir

# y esto no funcionara: var=50
var=50

echo "var => $var"

hello()
{
	echo "Hello world"
}

readonly -f hello
#Poner el -f es lo mismo pero especifico para fucniones

hello()
{
	echo "Hello worlddvsatyvdytasvtyd"
}


#si ponemos este comando solo en el codigo: readonly o readonly -p
#nos imprimira lo que acepta el readonly