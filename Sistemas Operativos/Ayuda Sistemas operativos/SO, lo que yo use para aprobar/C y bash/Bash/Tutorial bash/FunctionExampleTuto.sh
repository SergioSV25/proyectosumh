#! /bin/bash



usage()
{
	echo "You need to provide an argument: "
	echo "Usage : $0 file_name"
	#$0 te devuelve el nombre del archivo

}


is_file_exist()
{
	local file="$1"
	[[ -f "$file" ]] && return 0 || return 1
	#Lo que hay entre corchetes te va a devolver 1 si existe el fichero
	#Entonces se comprueba con el 0 y el 1
	#Si es 1 &&	0 no es valdio y se va a 1 || 1
	#En el caso de que no exista 0 && 0 ok.
	#PD: Yo lo haria con if else
}

[[ $# -eq 0 ]] &&usage 

if( is_file_exist "$1")
then
	echo "File Found"
else
	
	echo "File not Found"
fi	

