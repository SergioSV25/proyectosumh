#! /bin/bash

#No hace falta la plabar fucntion es solo para saber
#que es una function

function print(){
	#Variable local
	local name=$1
	echo "The name is $name"
}

#Variable global
name="Tom"

echo "The name is $name"

print max

echo "The name is $name"
