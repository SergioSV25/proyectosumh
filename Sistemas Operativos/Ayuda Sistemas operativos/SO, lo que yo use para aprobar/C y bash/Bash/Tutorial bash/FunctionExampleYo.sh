#! /bin/bash

#Esta es la version modificada hecha por mi 
#Ya que creo que es mas facile entenderlo asi

usage()
{
	echo "You need to provide an argument: "
	echo "Usage : $0 file_name"
	#$0 te devuelve el nombre del archivo en el que estas
}


is_file_exist()
{
	local file=$1
	if [[ -f $file ]]
	then
		return 1
		#Si el archivo existe devuelve 1
	else
		return 0
		#Si el archivo no existe devuelve 0
	fi
}

	

if( is_file_exist $1 )
then
	#Si el archivo no ha sido encontrado devuelve: 
	usage
	echo "File not Found"	
else
	#Si el archivo si ha sido encontrado devuelve:
	echo "File Found"
		
fi	

