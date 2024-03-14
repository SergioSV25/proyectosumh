#! /bin/bash


if [[ $# -ne 1 ]]
then 
	FICH=$(date +%Y%m%d)_home.tar.gz
	tar -czf $FICH --exclude=".*" --exclude-backups $HOME 
	#En este caso no se pone $1 porque no se le pasa nada 
	#y por ende se crea en el direcotorio en el que estamos 
else
	if [[ -d $1 ]] 
	then
		#aqui creamos el backup en la ruta que le pasemos
		FICH=$1/$(date +%Y%m%d)_home.tar.gz
		tar -czf $FICH --exclude=".*" --exclude-backups $HOME 
		#FICH= a todo eso porque queremos que se llame asi:yyyymmdd_home.tar.gz
		#el comando tar -czf es para comprimir los archivos
		#Hay que utilizar lo de exclude porque lo pide
		#en ambos casos tenemos que poner $1 antes porque 
		#necesitamos saber la ruta 
	else
		#aqui creamos el backup en la ruta que le pasemos,
		#pero como esa ruta no existe se crea y se gurada dentro de ella.
		mkdir $1
		FICH=$1/$(date +%Y%m%d)_home.tar.gz
		tar -czf $FICH --exclude=".*" --exclude-backups $HOME 

	fi
fi	
	




