#! /bin/bash
#! /bin/bash

usage ()
{
	echo "Opciones: [-s <Parametros>] o [-h <Parametros>]"
}

 

 cd $2

while getopts s:h param
do
	case $param in

	s)
		echo "Has seleccionado -s"
		ls -$param
		;;
	
	h)	
		echo "Has seleccionado -h"
		ls -$param
		;;
		
	*)
		usage
		echo "Argumento invalido"
	esac
done			