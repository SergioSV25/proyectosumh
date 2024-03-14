#! /bin/bash

echo -e "Enter the name of the file or directory: \c"
read fileName

#Forma 1
if [[ -f $fileName ]]
then
	if [ -w $fileName ]
	then
		echo "Type some text data. To quit press ctrl+d"
		# si al cat le ponemos > se reescribira el archivo
		#pero si escribimos cat>> se añadira a lo ya existente
		cat >> $fileName
	else
		echo "The file do not have writing permisions"
	fi	
else
	echo "$fileName not exists"	
fi	
