#! /bin/bash

num1=20.5
num2=5

#Forma 1
#El bc es una funcion calculadora, es decir, sirve para hacer operciones simples
#Funciona como:
#Se le pasa la opercaion | bc y ya estaria
#scale= num; sirve paraver cuantos decimales queremos
echo "$num1+$num2" | bc
echo "$num1-$num2" | bc
echo "$num1*$num2" | bc
echo "scale=20;$num1/$num2" | bc
echo "$num1%$num2" | bc

num=4

#el -l al final para llamar a la libreria de la raiz cuadrada
echo "scale=2;sqrt($num)" | bc -l
echo "scale=2;3^3" | bc -l