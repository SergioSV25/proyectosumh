#! /bin/bash

userHome=~ 

while IFS= read -r line
do
	echo $line
	nacion=(${line//-/ })
	touch ${nacion[3]}.txt
		while IFS= read -r line
		do
			cat > ${nacion[3]}.txt
		done < $1
done < $1


#Notas sobre este ejercicio:
#Lo que he ehcho ha sido leer line a linea el archivo y guardarlo en
#una variable, luego he dividido esa cada linea en un vector y
#he cogido la posicion 3 que es donde esta el pais.
#Una vez tengamos esto, cremos los txts con el nombre del pais
#luego dentro uso el mismo for para leer linea a linea e
#introducirlas en cada uno de los txts.