#! /bin/bash

#No hace falta la palabra function es solo para saber
#que es una function

function print(){
	echo $1 $2
}

quit (){
	exit
}




print hello hi
print world you

quit