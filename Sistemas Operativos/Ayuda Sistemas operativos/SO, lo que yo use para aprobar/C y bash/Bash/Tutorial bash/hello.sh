#! /bin/bash
#echo es para imprimir lineas
echo "Hello World"

# $('''') es para las variables 
#Lo de abajo tiene que ser en mayus si o si, sino no funciona.
echo Our shell name is $BASH
echo Our shell name version is $BASH_VERSION
echo Our home directory is $HOME
echo Our current working directory is $PWD

#VARIABLES DEFINIDAS POR EL USUARIO:

name=Manuel
val=10
echo The name is $name
echo value $val