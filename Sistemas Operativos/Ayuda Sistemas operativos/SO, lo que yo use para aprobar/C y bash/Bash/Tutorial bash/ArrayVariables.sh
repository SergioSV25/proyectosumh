#! /bin/bash

os=('ubuntu' 'windows' 'kali')
#Para añadir en la posicion indicada otro elemento
#Para remplazar un elemento: os[0]='macintosh'
os[6]='macintosh'

#Para eleminar el elemento en esa posicion 
unset os[2]

#Para imprimir todos
echo "${os[@]}"
#Para imprimir uno
echo "${os[1]}"
#Para imprimir el numero de posicion 
echo "${!os[@]}"
#Para imprimir el ultimo numero del array que no esta ocupado
echo "${#os[@]}"

string=dsadsaygdysagyd
echo "${string[@]}"
#Como todo el string se guarda en la posicion o si imprimimos la 1 no saldra nada
echo "${string[1]}"